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


// =========================================================================================================


// Homework6

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
    KPGM(igEdge).Save("./output/edge4Hough.pgm");

    // 허프 변환을 위한 초기화
    int rows = igEdge.Row();                 // 이미지의 세로 크기
    int cols = igEdge.Col();                 // 이미지의 가로 크기
    int minR = ui->editMinR->text().toInt(); // 탐지할 원의 최소 반지름
    int maxR = ui->editMaxR->text().toInt(); // 탐지할 원의 최대 반지름

    // 허프 공간(houghSpace)을 3D 배열로 할당 (세로, 가로, 반지름)
    std::vector<std::vector<std::vector<int>>>
        houghSpace(rows, std::vector<std::vector<int>>(cols, std::vector<int>(maxR - minR + 1, 0)));

    // 허프 변환: 에지 픽셀에서 원의 중심 좌표와 반지름에 투표
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // 에지 픽셀만 처리 (값이 0보다 큰 경우)
            if (igEdge[y][x] > 0) {
                // 탐지 가능한 모든 반지름에 대해 투표
                for (int r = minR; r <= maxR; ++r) {
                    for (int theta = 0; theta < 360; ++theta) {
                        // 중심 좌표 (a, b) 계산
                        int a = x - r * cos(theta * M_PI / 180.0);
                        int b = y - r * sin(theta * M_PI / 180.0);
                        // 중심 좌표가 이미지 범위 안에 있는 경우 허프 공간에 투표
                        if (a >= 0 && a < cols && b >= 0 && b < rows) {
                            houghSpace[b][a][r - minR]++;
                        }
                    }
                }
            }
        }
    }

    // 허프 공간에서 최대값을 기준으로 원 검출
    std::vector<std::tuple<int, int, int>> detectedCircles; // (중심 X, 중심 Y, 반지름)
    int threshold = ui->editThreshVote->text().toInt(); // 허프 변환의 투표 임계값
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            for (int r = 0; r < maxR - minR + 1; ++r) {
                // 투표 수가 임계값 이상인 경우 원으로 검출
                if (houghSpace[y][x][r] >= threshold) {
                    detectedCircles.emplace_back(x, y, r + minR);
                }
            }
        }
    }

    // 검출된 원들 중 상위 3개를 선택 (투표 수 기준 정렬)
    std::sort(detectedCircles.begin(), detectedCircles.end(),
              [&houghSpace, &minR](const auto& a, const auto& b) {
                  return houghSpace[std::get<1>(a)][std::get<0>(a)][std::get<2>(a) - minR] >
                         houghSpace[std::get<1>(b)][std::get<0>(b)][std::get<2>(b) - minR];
              });

    for (size_t i = 0; i < std::min(detectedCircles.size(), size_t(3)); ++i) {
        auto [cx, cy, radius] = detectedCircles[i];
        // 검출된 원 정보를 출력
        qDebug() << "Circle " << i + 1 << ": Center=(" << cx << "," << cy << "), Radius=" << radius;
    }

    // 결과를 출력창에 시각화
    ImageForm* q_pForm = nullptr;
    for (auto item : _lImageForm) {
        // 동일한 이름과 크기의 출력창이 이미 존재하면 재사용
        if (item->ID() == "Circle Localization" && item->size() == _q_pFormFocused->size()) {
            q_pForm = item;
            q_pForm->Update(igMain.GrayToRGB());
            break;
        }
    }

    // 동일한 출력창이 없으면 새로 생성
    if (q_pForm == nullptr) {
        q_pForm = new ImageForm(igMain.GrayToRGB(), "Circle Localization", this);
        _lImageForm.push_back(q_pForm);
    }

    // 검출된 원을 출력창에 그리기
    for (size_t i = 0; i < std::min(detectedCircles.size(), size_t(3)); ++i) {
        auto [cx, cy, radius] = detectedCircles[i];
        q_pForm->DrawEllipse(QPoint((int)(cx), (int)(cy)),  // 원의 중심 좌표
                             (int)(radius), (int)(radius),  // 원의 반지름
                             QColor(255, 0, 0), 2);         // 빨간색으로 원 그리기
        // 리스트 위젯에 결과 추가
        if (!ui->listWidget->isVisible())
            on_buttonShowList_clicked();
        ui->listWidget->insertItem(0, QString(">> detected circle --> center=(%1, %2), radius=%3")
                                          .arg(cx)
                                          .arg(cy)
                                          .arg(radius));
    }

    // 출력창 업데이트 및 표시
    q_pForm->update();
    q_pForm->show();

    // UI 상태를 갱신 (버튼 활성화 등)
    UpdateUI();
}
