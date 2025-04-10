#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"
#include "edge.h"
#include "corner.h"
#include "circleHough.h"

#include <QFileDialog>
#include <QPainter>
#include <sstream>
#include <fstream>
#include <random>

using namespace std;

MainFrame::MainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    _q_pFormFocused     = 0;

    //객체 맴버의 초기화


    //리스트 출력창을 안보이게    
    ui->listWidget->setVisible(false);
    this->adjustSize();

    //UI 활성화 갱신
    UpdateUI();
}

MainFrame::~MainFrame()
{ 
    delete ui;         

    for(auto& item : _lImageForm)
        delete item;

}

void MainFrame::CloseImageForm(ImageForm *pForm)
{
    //ImageForm 포인터 삭제
    unsigned int idx = std::find(_lImageForm.begin(), _lImageForm.end(), pForm) - _lImageForm.begin();
    if(idx != _lImageForm.size())
    {
        delete _lImageForm[idx];
        _lImageForm.erase(_lImageForm.begin() + idx);
    }

    //활성화 ImageForm 초기화
    _q_pFormFocused     = 0;

    //관련 객체 삭제

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::UpdateUI()
{    
    if(ui->tabWidget->currentIndex() == 0)
    {
    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
    }
    else if(ui->tabWidget->currentIndex() == 3)
    {
    }
    else if(ui->tabWidget->currentIndex() == 5)
    {
    }
}

void MainFrame::OnMousePos(const int &nX, const int &nY, ImageForm* q_pForm)
{
}

void MainFrame::focusInEvent(QFocusEvent * event)
{
    Q_UNUSED(event) ;

    UpdateUI();
}

void MainFrame::closeEvent(QCloseEvent* event)
{
    //생성된 ImageForm을 닫는다.
    for(int i=0; i< _lImageForm.size(); i++)
        delete _lImageForm[i];

    //리스트에서 삭제한다.
    _lImageForm.clear();
}


void MainFrame::on_buttonOpen_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;

    //이미지 출력을 위한 ImageForm 생성    
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "OPEN", this);

    _lImageForm.push_back(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_buttonDeleteContents_clicked()
{
    //생성된 ImageForm을 닫는다.
    for(int i=_lImageForm.size()-1; i>=0; i--)
        delete _lImageForm[i];

    //리스트에서 삭제한다.
    _lImageForm.clear();

    //객체 삭제


    ui->listWidget->clear();
}

void MainFrame::on_tabWidget_currentChanged(int index)
{
    static int nOld = -1;

    if(nOld == 0)
    {

    }
    else if(nOld == 1)
    {

    }
    nOld = index;

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_buttonShowList_clicked()
{
    static int nWidthOld = ui->tabWidget->width();

    if(ui->listWidget->isVisible())
    {
        nWidthOld = ui->listWidget->width();
        ui->listWidget->hide();
        this->adjustSize();
    }
    else
    {        
        ui->listWidget->show();
        QRect q_rcWin = this->geometry();

        this->setGeometry(q_rcWin.left(), q_rcWin.top(), q_rcWin.width()+nWidthOld, q_rcWin.height());
    }
}

void MainFrame::on_pushCircleLocalization_clicked()
{
    // 현재 포커스된 이미지 폼에서 그레이스케일 이미지를 가져옴
    KImageGray igMain = _q_pFormFocused->ImageGray();

    // Canny 에지 검출 객체 생성
    KEdge oEdge(2);
    KImageGray igEdge;
    // Canny 에지 검출 실행
    oEdge.Canny(10, 30, igMain, igEdge);

    // 에지 검출 결과를 파일로 저장 (디버깅용)
    KPGM(igEdge).Save("./output/edge4Mask.pgm");

    // 마스크 좌표 로드
    std::vector<std::pair<int, int>> maskModel;
    std::ifstream maskFile("./output/mask.txt");
    if (!maskFile.is_open()) {
        qDebug() << "Failed to open mask.txt";
        return;
    }

    std::string firstLine;
    std::getline(maskFile, firstLine); // 첫 번째 줄 읽기
    if (firstLine != "1") { // '1'이 아닌 경우 처리
        qDebug() << "Unexpected first line in mask.txt: " << QString::fromStdString(firstLine);
        return;
    }

    int numPoints;
    maskFile >> numPoints; // 마스크의 점 개수 읽기
    for (int i = 0; i < numPoints; ++i) {
        int x, y;
        maskFile >> x >> y;
        maskModel.emplace_back(x, y);
    }
    maskFile.close();

    // 마스크 크기 계산 (originalMaskWidth, originalMaskHeight)
    int minX = INT_MAX, maxX = INT_MIN;
    int minY = INT_MAX, maxY = INT_MIN;
    for (const auto& [x, y] : maskModel) {
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }
    int originalMaskWidth = maxX - minX + 1;
    int originalMaskHeight = maxY - minY + 1;

    qDebug() << "Original Mask Dimensions: Width=" << originalMaskWidth << ", Height=" << originalMaskHeight;

    // 마스크 좌표를 이미지 크기에 맞게 스케일링
    double scaleX = static_cast<double>(igEdge.Col()) / originalMaskWidth;
    double scaleY = static_cast<double>(igEdge.Row()) / originalMaskHeight;

    std::vector<std::pair<int, int>> scaledMaskModel;
    for (const auto& [dx, dy] : maskModel) {
        int scaledX = static_cast<int>((dx - minX) * scaleX); // 마스크 좌표 스케일링
        int scaledY = static_cast<int>((dy - minY) * scaleY);
        scaledMaskModel.emplace_back(scaledX, scaledY);
    }

    // 출력 창에 마스크를 시각화
    ImageForm* q_pForm = nullptr;
    for (auto item : _lImageForm) {
        if (item->ID() == "Mask Visualization" && item->size() == _q_pFormFocused->size()) {
            q_pForm = item;
            q_pForm->Update(igMain.GrayToRGB());
            break;
        }
    }

    if (q_pForm == nullptr) {
        q_pForm = new ImageForm(igMain.GrayToRGB(), "Mask Visualization", this);
        _lImageForm.push_back(q_pForm);
    }

    // 마스크 좌표를 시각화
    for (const auto& [x, y] : scaledMaskModel) {
        q_pForm->DrawEllipse(QPoint(x, y), 2, 2, QColor(0, 255, 0), -1); // 초록색 점으로 표시
    }

    // 출력창 업데이트 및 표시
    q_pForm->update();
    q_pForm->show();

    // 허프 공간 초기화
    int rows = igEdge.Row();
    int cols = igEdge.Col();
    std::vector<std::vector<int>> houghSpace(rows, std::vector<int>(cols, 0));

    // 허프 변환: 에지 픽셀에서 마스크 모델을 사용하여 투표
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (igEdge[y][x] > 0) {
                for (const auto& [dx, dy] : scaledMaskModel) {
                    int a = x - dx;
                    int b = y - dy;
                    if (a >= 0 && a < cols && b >= 0 && b < rows) {
                        houghSpace[b][a]++;
                    }
                }
            }
        }
    }

    // 투표 수 기준으로 상위 결과 시각화
    int threshold = ui->editThreshVote->text().toInt(); // 투표 임계값
    std::vector<std::tuple<int, int, int>> voteResults; // (x, y, votes)
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (houghSpace[y][x] > threshold) {
                voteResults.emplace_back(x, y, houghSpace[y][x]);
            }
        }
    }

    // 투표 수 기준 정렬
    std::sort(voteResults.begin(), voteResults.end(), [](const auto& a, const auto& b) {
        return std::get<2>(a) > std::get<2>(b); // votes 기준 정렬
    });

    for (size_t i = 0; i < std::min(voteResults.size(), size_t(3)); ++i) {
        auto [x, y, votes] = voteResults[i];
        qDebug() << "Center=(" << x << "," << y << "), Votes=" << votes;
    }

    // UI 상태를 갱신
    UpdateUI();
}


// =========================================================================================================

// Homework7

void MainFrame::on_pushMaskVisualization_clicked()
{
    // 1. 마스크 좌표 로드
    std::vector<std::pair<int, int>> maskModel;
    std::ifstream maskFile("./output/mask.txt");
    if (!maskFile.is_open()) { // 파일 열기 실패 시 처리
        qDebug() << "Failed to open mask.txt";
        return;
    }

    std::string firstLine;
    std::getline(maskFile, firstLine); // 첫 번째 줄 읽기
    if (firstLine != "1") { // '1'이 아닌 경우 처리
        qDebug() << "Unexpected first line in mask.txt: " << QString::fromStdString(firstLine);
        return;
    }

    int numPoints;
    maskFile >> numPoints; // 마스크의 점 개수 읽기
    for (int i = 0; i < numPoints; ++i) {
        int x, y;
        maskFile >> x >> y;
        maskModel.emplace_back(x, y);
    }
    maskFile.close(); // 파일 닫기

    // 2. 마스크 크기 계산
    int minX = INT_MAX, maxX = INT_MIN;
    int minY = INT_MAX, maxY = INT_MIN;
    for (const auto& [x, y] : maskModel) {
        if (x < minX) minX = x; // X 좌표의 최소값 갱신
        if (x > maxX) maxX = x; // X 좌표의 최대값 갱신
        if (y < minY) minY = y; // Y 좌표의 최소값 갱신
        if (y > maxY) maxY = y; // Y 좌표의 최대값 갱신
    }
    int originalMaskWidth = maxX - minX + 1;
    int originalMaskHeight = maxY - minY + 1;

    qDebug() << "Original Mask Dimensions: Width=" << originalMaskWidth << ", Height=" << originalMaskHeight;

    // 3. 백지 이미지 생성 (마스크 크기에 맞춤)
    int blankWidth = originalMaskWidth + 50; // 마스크 너비 + 여유 공간
    int blankHeight = originalMaskHeight + 50; // 마스크 높이 + 여유 공간
    KImageColor blankImage(blankHeight, blankWidth); // 흰색 이미지 생성
    // blankImage.Clear(255, 255, 255); // 백지를 흰색으로 초기화

    // 4. 마스크 좌표를 백지 위에 시각화
    ImageForm* q_pForm = nullptr;
    q_pForm = new ImageForm(blankImage, "Mask Visualization", this);
    _lImageForm.push_back(q_pForm);

    for (const auto& [x, y] : maskModel) {
        int shiftedX = x - minX + 25; // 좌표를 백지 이미지 중앙으로 이동
        int shiftedY = y - minY + 25;
        q_pForm->DrawEllipse(QPoint(shiftedX, shiftedY), 2, 2, QColor(0, 255, 0), 1); // 초록색 점으로 시각화
    }

    // 5. 출력창 업데이트 및 표시
    q_pForm->update();
    q_pForm->show();

    qDebug() << "Mask visualization on blank completed!";
}



void MainFrame::on_pushGeneralizedHoughTransform_clicked()
{
    // Shape Table 초기화
    // mask.txt을 불러옴
    std::ifstream maskFile("./output/mask.txt");
    if (!maskFile.is_open()) {
        qDebug() << "Failed to open mask.txt";
        return;
    }

    // 첫 번째 줄 "1" 무시
    std::string firstLine;
    std::getline(maskFile, firstLine);

    // 좌표값 저장
    int numPoints;
    maskFile >> numPoints;
    std::vector<std::pair<int, int>> maskModel;
    for (int i = 0; i < numPoints; ++i) {
        int x, y;
        maskFile >> x >> y;
        maskModel.emplace_back(x, y);
    }
    maskFile.close();

    // Shape Table 초기화 코드 수정
    int minX = INT_MAX, maxX = INT_MIN, minY = INT_MAX, maxY = INT_MIN;

    // 마스크의 경계 계산 (중심점을 찾기 위해)
    for (const auto& [x, y] : maskModel) {
        if (x < minX) minX = x;
        if (x > maxX) maxX = x;
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }

    // 마스크 중심 좌표 계산
    int centerX = (minX + maxX) / 2;
    int centerY = (minY + maxY) / 2;

    // Shape Table 초기화 (360개 방향 섹터)
    std::vector<std::vector<std::pair<double, double>>> shapeTable(360);

    // Shape Table 작성
    for (size_t i = 0; i < maskModel.size(); ++i) {
        int x = maskModel[i].first;
        int y = maskModel[i].second;

        // 이전 점과 다음 점 계산 (윤곽선의 에지 방향 계산을 위해)
        int xPrev = maskModel[(i == 0 ? maskModel.size() - 1 : i - 1)].first;
        int yPrev = maskModel[(i == 0 ? maskModel.size() - 1 : i - 1)].second;
        int xNext = maskModel[(i + 1) % maskModel.size()].first;
        int yNext = maskModel[(i + 1) % maskModel.size()].second;

        // 에지의 접선 방향 계산 (각도: -π ~ π)
        double edgeAngle = std::atan2(yNext - yPrev, xNext - xPrev);

        // 에지의 수직 방향(법선 방향) 계산
        double normalAngle = edgeAngle + M_PI / 2; // 법선 방향: -π ~ π

        // 180도 반대 방향을 통일하여 0 ~ π 범위로 조정
        if (normalAngle < 0) {
            normalAngle += M_PI; // 음수를 양수로 변환
        } else if (normalAngle > M_PI) {
            normalAngle -= M_PI; // π를 초과하는 경우 π 내로 조정
        }

        // 중심점으로부터의 거리 계산
        double r = std::sqrt((x - centerX) * (x - centerX) + (y - centerY) * (y - centerY));

        // 중심점으로부터의 각도 계산
        double dx = x - centerX;
        double dy = y - centerY;
        double alpha = std::atan2(dy, dx);

        // 법선 방향을 360개 방향 섹터로 나누기
        int phi = static_cast<int>((normalAngle + M_PI) / (2 * M_PI / 360)) % 360;

        // 해당 방향 섹터에 거리(r)와 중심으로부터의 각도를 저장
        shapeTable[phi].emplace_back(r, alpha);
    }

    // Shape Table 디버깅 출력
    for (int i = 0; i < 360; ++i) {
        qDebug() << "Direction" << i << "Shape Points:";
        for (const auto& [r, alpha] : shapeTable[i]) {
            qDebug() << "  r =" << r << ", alpha =" << alpha;
        }
    }

    // 현재 포커스된 이미지 폼에서 그레이스케일 이미지를 가져옴
    KImageGray igMain = _q_pFormFocused->ImageGray();

    // Canny Edge Detection으로 에지 검출
    KEdge oEdge(1.3); // Sigma 값 설정
    KImageGray igEdge;
    oEdge.Canny(15, 70, igMain, igEdge); // 하한: 15, 상한: 70, Sigma=1.3 (블러 효과)

    // 디버깅용 에지 이미지 저장
    KPGM(igEdge).Save("./output/edgeInput.pgm");

    // 기울기값 구하기 위해 Sobel 필터 구현
    const int sobelXKernel[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    const int sobelYKernel[3][3] = {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };

    // 이미지의 행, 열 크기 저장, Sobel 필터 적용할 이미지 생성
    int rows = igEdge.Row();
    int cols = igEdge.Col();
    KImageGray sobelX(rows, cols), sobelY(rows, cols);

    // Sobel 필터 적용
    for (int y = 1; y < rows - 1; ++y) {
        for (int x = 1; x < cols - 1; ++x) {
            int gradX = 0, gradY = 0;
            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    gradX += igEdge[y + ky][x + kx] * sobelXKernel[ky + 1][kx + 1];
                    gradY += igEdge[y + ky][x + kx] * sobelYKernel[ky + 1][kx + 1];
                }
            }
            sobelX[y][x] = gradX;
            sobelY[y][x] = gradY;
        }
    }

    // Sobel X 이미지 시각화
    ImageForm* q_pFormX = nullptr;
    for (auto item : _lImageForm) {
        if (item->ID() == "Sobel X Result" && item->size() == _q_pFormFocused->size()) {
            q_pFormX = item;
            q_pFormX->Update(sobelX.GrayToRGB());
            break;
        }
    }

    if (q_pFormX == nullptr) {
        q_pFormX = new ImageForm(sobelX.GrayToRGB(), "Sobel X Result", this);
        _lImageForm.push_back(q_pFormX);
    }

    q_pFormX->update();
    q_pFormX->show();

    // Sobel Y 이미지 시각화
    ImageForm* q_pFormY = nullptr;
    for (auto item : _lImageForm) {
        if (item->ID() == "Sobel Y Result" && item->size() == _q_pFormFocused->size()) {
            q_pFormY = item;
            q_pFormY->Update(sobelY.GrayToRGB());
            break;
        }
    }

    if (q_pFormY == nullptr) {
        q_pFormY = new ImageForm(sobelY.GrayToRGB(), "Sobel Y Result", this);
        _lImageForm.push_back(q_pFormY);
    }

    q_pFormY->update();
    q_pFormY->show();

    // Generalized Hough Transform - 4차원 Accumulator Array 초기화
    const double scaleInit = 0.35;
    const double scaleUnit = 0.01;
    const int scaleBins = 10;  // 스케일 범위: 0.35 ~ 0.45 (0.01 단위, 총 10개)
    const int thetaBins = 360; // θ 범위: 1도 간격 (0~359)

    // Accumulator Array 생성: rows x cols x scaleBins x thetaBins
    std::vector<std::vector<std::vector<std::vector<int>>>> accumulator(
        rows,
        std::vector<std::vector<std::vector<int>>>(
            cols,
            std::vector<std::vector<int>>(
                scaleBins,
                std::vector<int>(thetaBins, 0)
                )
            )
        );

    // Accumulator Array 업데이트
    for (int y = 1; y < rows - 1; ++y) {
        for (int x = 1; x < cols - 1; ++x) {
            if (igEdge[y][x] > 0) { // 에지 픽셀인 경우 계산
                double gradX = static_cast<double>(sobelX[y][x]);
                double gradY = static_cast<double>(sobelY[y][x]);
                double edgeAngle = std::atan2(gradY, gradX); // 에지 방향 (-π ~ π)

                // 모든 θ에 대해 투표
                for (int theta = 0; theta < thetaBins; ++theta) {
                    double thetaRad = theta * (M_PI / 180.0); // θ를 라디안으로 변환
                    double phi = edgeAngle - thetaRad; // Shape Table에서 사용할 각도

                    // phi를 0 ~ π 범위로 통일
                    if (phi < 0) {
                        phi += M_PI; // 음수를 양수로 변환
                    } else if (phi > M_PI) {
                        phi -= M_PI; // π를 초과하는 경우 π 내로 조정
                    }

                    // Shape Table 탐색
                    int phiIndex = static_cast<int>((phi + M_PI) / (2 * M_PI / 16)) % 16;
                    for (const auto& [r, alpha] : shapeTable[phiIndex]) {
                        // 모든 스케일에 대해 투표
                        for (int scaleIdx = 0; scaleIdx < scaleBins; ++scaleIdx) {
                            double s = scaleInit + scaleIdx * scaleUnit;

                            // 중심 좌표 계산
                            int centerX = static_cast<int>(x - s * r * std::cos(alpha + thetaRad));
                            int centerY = static_cast<int>(y - s * r * std::sin(alpha + thetaRad));

                            // 유효한 중심 좌표인지 확인 후 Accumulator Array 값 증가
                            if (centerX >= 0 && centerX < cols && centerY >= 0 && centerY < rows) {
                                accumulator[centerY][centerX][scaleIdx][theta]++;
                            }
                        }
                    }
                }
            }
        }
        // x 픽셀에 대한 허프 변환 완료 후 디버깅 출력
        qDebug() << "Accumulator Array Update: " << y << " / " << rows;
    }

    // 누적 배열을 기반으로 투표수 시각화 (Grayscale 이미지 생성)
    KImageGray votingResult(rows, cols);

    // 각 픽셀의 최대 투표수를 계산하여 그레이스케일로 저장
    int maxAccumulatorValue = 0;

    // 누적 배열의 최대값을 찾음
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            int maxPixelVotes = 0;
            for (int scaleIdx = 0; scaleIdx < scaleBins; ++scaleIdx) {
                for (int theta = 0; theta < thetaBins; ++theta) {
                    maxPixelVotes = std::max(maxPixelVotes, accumulator[y][x][scaleIdx][theta]);
                }
            }
            votingResult[y][x] = maxPixelVotes; // 임시로 최대값 저장
            maxAccumulatorValue = std::max(maxAccumulatorValue, maxPixelVotes); // 최대값 갱신
        }
    }

    // 투표수 그레이스케일 정규화 (0 ~ 255)
    if (maxAccumulatorValue > 0) {
        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                votingResult[y][x] = static_cast<int>(
                    (votingResult[y][x] / static_cast<double>(maxAccumulatorValue)) * 255.0);
            }
        }
    }

    // 투표수 이미지 시각화
    ImageForm* q_pVotingForm = nullptr;
    for (auto item : _lImageForm) {
        if (item->ID() == "Voting Result" && item->size() == _q_pFormFocused->size()) {
            q_pVotingForm = item;
            q_pVotingForm->Update(votingResult.GrayToRGB());
            break;
        }
    }

    if (q_pVotingForm == nullptr) {
        q_pVotingForm = new ImageForm(votingResult.GrayToRGB(), "Voting Result", this);
        _lImageForm.push_back(q_pVotingForm);
    }

    q_pVotingForm->update();
    q_pVotingForm->show();

    qDebug() << "Voting result image generated and displayed!";

    // 디버깅용 투표 이미지 저장
    KPGM(votingResult).Save("./output/votingResult.pgm");

    // 투표수가 70 이상인 모든 점을 기록
    std::vector<std::tuple<int, int, int, int, int>> validVotes; // (votes, x, y, scaleIdx, theta)

    // 누적 배열 탐색
    for (int y = 2; y < rows-2; ++y) {
        for (int x = 2; x < cols-2; ++x) {
            for (int scaleIdx = 0; scaleIdx < scaleBins; ++scaleIdx) {
                for (int theta = 0; theta < thetaBins; ++theta) {
                    int currentVotes = accumulator[y][x][scaleIdx][theta];

                    // 투표수가 70 이상인 경우 저장
                    if (currentVotes >= 70) {
                        validVotes.emplace_back(currentVotes, x, y, scaleIdx, theta);
                    }
                }
            }
        }
    }

    // 투표수를 기록 완료 후 디버깅 출력
    for (const auto& [votes, x, y, scaleIdx, theta] : validVotes) {
        qDebug() << "Votes:" << votes << ", Center:(" << x << "," << y
                 << "), ScaleIdx:" << scaleIdx << ", Theta:" << theta;
    }

    // 마스크 시각화 (투표수가 임계치 이상인 점)
    ImageForm* q_pForm_valid = nullptr;
    for (auto item : _lImageForm) {
        if (item->ID() == "GHT Result Valid" && item->size() == _q_pFormFocused->size()) {
            q_pForm_valid = item;
            q_pForm_valid->Update(igMain.GrayToRGB());
            break;
        }
    }
    if (q_pForm_valid == nullptr) {
        q_pForm_valid = new ImageForm(igMain.GrayToRGB(), "GHT Result Valid", this);
        _lImageForm.push_back(q_pForm_valid);
    }

    // 유효한 투표 위치에 대해 마스크 모델을 그림
    for (const auto& [votes, x, y, scaleIdx, theta] : validVotes) {
        // 스케일 계산
        double scale = scaleInit + scaleIdx * scaleUnit;
        double thetaRad = theta * (M_PI / 180.0); // 각도를 라디안으로 변환

        // 마스크 모델 시각화
        for (size_t i = 0; i < maskModel.size(); ++i) {
            int maskX = maskModel[i].first;
            int maskY = maskModel[i].second;

            // 중심점으로부터의 거리 계산
            double r = std::sqrt((maskX - centerX) * (maskX - centerX) +
                                 (maskY - centerY) * (maskY - centerY));

            // 중심점으로부터의 각도 계산
            double dx = maskX - centerX;
            double dy = maskY - centerY;
            double alpha = std::atan2(dy, dx);

            // 모델 좌표를 중심 좌표 기준으로 변환
            double transformedX = x + scale * (r * std::cos(alpha + thetaRad));
            double transformedY = y + scale * (r * std::sin(alpha + thetaRad));

            // 변환된 좌표를 원으로 표시
            q_pForm_valid->DrawEllipse(QPoint(static_cast<int>(transformedX),
                                              static_cast<int>(transformedY)), 2, 2, QColor(0, 255, 0), 1);
        }

        // 중심 점 시각화
        q_pForm_valid->DrawEllipse(QPoint(x, y), static_cast<int>(10 * scale),
                                   static_cast<int>(10 * scale), QColor(255, 0, 0), 2);

        qDebug() << "Votes >= 70: Center=(" << x << "," << y << "), Scale=" << scale << ", Theta=" << theta;
    }

    q_pForm_valid->update();
    q_pForm_valid->show();


    // 마스크 시각화 (투표수가 최대값인 점)
    ImageForm* q_pForm_max = nullptr;
    for (auto item : _lImageForm) {
        if (item->ID() == "GHT Result Max" && item->size() == _q_pFormFocused->size()) {
            q_pForm_max = item;
            q_pForm_max->Update(igMain.GrayToRGB());
            break;
        }
    }
    if (q_pForm_max == nullptr) {
        q_pForm_max = new ImageForm(igMain.GrayToRGB(), "GHT Result Max", this);
        _lImageForm.push_back(q_pForm_max);
    }

    // 투표수가 최대인 점 찾기
    if (!validVotes.empty()) {
        // 최대값을 찾기 위해 std::max_element 사용
        auto maxVoteIt = std::max_element(
            validVotes.begin(),
            validVotes.end(),
            [](const std::tuple<int, int, int, int, int>& a, const std::tuple<int, int, int, int, int>& b) {
                return std::get<0>(a) < std::get<0>(b);
            }
            );

        // 최대값 출력
        const auto& [votes, x, y, scaleIdx, theta] = *maxVoteIt;
        qDebug() << "Max Votes:" << votes << ", Center:(" << x << "," << y
                 << "), ScaleIdx:"<< scaleIdx << ", Theta:" << theta;

        // 스케일 계산
        double scale = scaleInit + scaleIdx * scaleUnit;
        double thetaRad = theta * (M_PI / 180.0); // 각도를 라디안으로 변환

        // 마스크 모델 시각화
        for (size_t i = 0; i < maskModel.size(); ++i) {
            int maskX = maskModel[i].first;
            int maskY = maskModel[i].second;

            // 중심점으로부터의 거리 계산
            double r = std::sqrt((maskX - centerX) * (maskX - centerX) +
                                 (maskY - centerY) * (maskY - centerY));

            // 중심점으로부터의 각도 계산
            double dx = maskX - centerX;
            double dy = maskY - centerY;
            double alpha = std::atan2(dy, dx);

            // 모델 좌표를 중심 좌표 기준으로 변환
            double transformedX = x + scale * (r * std::cos(alpha + thetaRad));
            double transformedY = y + scale * (r * std::sin(alpha + thetaRad));

            // 변환된 좌표를 원으로 표시
            q_pForm_max->DrawEllipse(QPoint(static_cast<int>(transformedX),
                                            static_cast<int>(transformedY)), 2, 2, QColor(255, 0, 0), 1);
        }

        // 중심 점 시각화
        q_pForm_max->DrawEllipse(QPoint(x, y), static_cast<int>(10 * scale), static_cast<int>(10 * scale),
                                 QColor(255, 0, 0), 2);

        qDebug() << "Votes >= 80: Center=(" << x << "," << y << "), Scale=" << scale << ", Theta=" << theta;

    } else {
        qDebug() << "No valid votes found.";
    }

    q_pForm_max->update();
    q_pForm_max->show();

    qDebug() << "Generalized Hough Transform completed";
}

