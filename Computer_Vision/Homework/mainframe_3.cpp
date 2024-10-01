#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"

#include <QFileDialog>
#include <QPainter>
#include <sstream>
#include <fstream>

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
        ui->pushOstu->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "OPEN" && _q_pFormFocused->ImageGray().Address());
        ui->pushThresholding->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "OPEN" && _q_pFormFocused->ImageGray().Address());
        ui->pushDilation->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "Binary Image" && _q_pFormFocused->ImageGray().Address());
        ui->pushErosion->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "Binary Image" && _q_pFormFocused->ImageGray().Address());
        ui->pushLabeling->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "Binary Image" && _q_pFormFocused->ImageGray().Address());
        }
    else if(ui->tabWidget->currentIndex() == 3)
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


void MainFrame::on_pushOstu_clicked()
{
    // Ostu thresholding
    KImageGray igMain = _q_pFormFocused->ImageGray();
    KImageGray igBin;
    KBINARIZATION_OUTPUT* opBinOutput = KHisto().Ostu(&igMain, &igBin);

    // 출력창 결정
    ImageForm* q_pForm = 0;
    for(auto item : _lImageForm)
        if(item->ID() == "Binary Image" && item->size() == _q_pFormFocused->size())
        {
            q_pForm = item;
            break;
        }

    // 기존 창에 표시
    if(q_pForm)
        q_pForm->Update(igBin);
    // 새로운 창에 표시
    else
    {
        q_pForm = new ImageForm(igBin, "Binary Image", this);
        q_pForm->show();
        _lImageForm.push_back(q_pForm);
    }

    // Threshold 값 표시
    ui->spinOstu->setValue(opBinOutput->nThresh);
    ui->listWidget->addItem(QString(">> Ostu Threshold : %1").arg(opBinOutput->nThresh));
    ui->listWidget->show();

    // UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_pushThresholding_clicked()
{
    // Tholding 적용
    KImageGray igMain = _q_pFormFocused->ImageGray();
    igMain.Thresholded(ui->spinOstu->value());

    // 출력창 결정
    ImageForm* q_pForm = 0;
    for(auto item : _lImageForm)
        if(item->ID() == "Binary Image" && item->size() == _q_pFormFocused->size())
        {
            q_pForm = item;
            break;
        }

    // 기존 창에 표시
    if(q_pForm)
        q_pForm->Update(igMain);
    // 새로운 창에 표시
    else
    {
        q_pForm = new ImageForm(igMain, "Binary Image", this);
        q_pForm->show();
        _lImageForm.push_back(q_pForm);
    }

    // Threshod 값 표시
    ui->listWidget->addItem(QString(">> Manual Threshold : %1").arg(ui->spinOstu->value()));
    ui->listWidget->show();

    // UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_pushHistogram_clicked()
{
    // 포커스 된 ImageForm으로부터 영상을 가져옴
    KImageGray igMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() && _q_pFormFocused->ID() == "OPEN")
        igMain = _q_pFormFocused->ImageGray();
    else
        return;

    // Histogram을 구함
    vector<int> lHisto(256);
    int nRow = igMain.Row();
    int nCol = igMain.Col();

    for(int i = 0; i < nRow; i++)
        for(int j = 0; j < nCol; j++)
            lHisto[ igMain[i][j] ] ++;

    // 파일에 저장
    ofstream fout("./output/histo.csv");
    for(auto item : lHisto)
        fout << item << ',';

    // 결과 표시
    if(ui->listWidget->isVisible() == false)
        on_buttonShowList_clicked();
    ui->listWidget->addItem(QString(">> finish histogramming --> histo.csv"));
}


// image dilation and erosion algorithm

void MainFrame::on_pushDilation_clicked()
{
    // Dilation
    KImageGray igBin = _q_pFormFocused->ImageGray();
    KImageGray igOut = _q_pFormFocused->ImageGray();

    // kernelSize 선택 3x3 or 5x5
    int kernelSize;
    if(ui->comboBoxDilation->currentIndex() == 0) kernelSize = 3;
    else kernelSize = 5;
    int halfKernel = kernelSize / 2;

    // Dilation
    for(int i = halfKernel; i < igBin.Row() - halfKernel; i++)
    {
        for(int j = halfKernel; j < igBin.Col() - halfKernel; j++)
        {
            if(igBin._ppA[i][j] == 0)
            {
                bool shouldDilate = false;
                // 커널 크기에 따라 주변을 검사
                for(int ki = -halfKernel; ki <= halfKernel; ki++)
                {
                    for(int kj = -halfKernel; kj <= halfKernel; kj++)
                    {
                        if(igBin._ppA[i + ki][j + kj] != 0)
                        {
                            shouldDilate = true;
                            break;
                        }
                    }
                    if(shouldDilate) break;
                }
                if(shouldDilate)
                {
                    igOut._ppA[i][j] = 255;
                }
            }
        }
    }

    ImageForm* q_pForm = 0;
    for(auto item : _lImageForm)
        if(item->ID() == "Binary Image" && item->size() == _q_pFormFocused->size())
        {
            q_pForm = item;
            break;
        }

    // 새로운 창에 표시
    q_pForm = new ImageForm(igOut, "Binary Image", this);
    q_pForm->show();
    _lImageForm.push_back(q_pForm);

    // UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_pushErosion_clicked()
{
    // Erosion
    KImageGray igBin = _q_pFormFocused->ImageGray();
    KImageGray igOut = _q_pFormFocused->ImageGray();

    // kernelSize 선택 3x3 or 5x5
    int kernelSize;
    if(ui->comboBoxErosion->currentIndex() == 0) kernelSize = 3;
    else kernelSize = 5;
    int halfKernel = kernelSize / 2;

    // Erosion
    for(int i = halfKernel; i < igBin.Row() - halfKernel; i++)
    {
        for(int j = halfKernel; j < igBin.Col() - halfKernel; j++)
        {
            if(igBin._ppA[i][j])
            {
                bool shouldErosion = false;
                // 커널 크기에 따라 주변을 검사
                for(int ki = -halfKernel; ki <= halfKernel; ki++)
                {
                    for(int kj = -halfKernel; kj <= halfKernel; kj++)
                    {
                        if(igBin._ppA[i + ki][j + kj] == 0)
                        {
                            shouldErosion = true;
                            break;
                        }
                    }
                    if(shouldErosion) break;
                }
                if(shouldErosion)
                {
                    igOut._ppA[i][j] = 0;
                }
            }
        }
    }

    ImageForm* q_pForm = 0;
    for(auto item : _lImageForm)
        if(item->ID() == "Binary Image" && item->size() == _q_pFormFocused->size())
        {
            q_pForm = item;
            break;
        }

    // 새로운 창에 표시
    q_pForm = new ImageForm(igOut, "Binary Image", this);
    q_pForm->show();
    _lImageForm.push_back(q_pForm);

    // UI 활성화 갱신
    UpdateUI();
}


// labeling algorithm

KImageColor ConvertToColor(const KImageWord& iwImg)
{
    int rows = iwImg.Row();
    int cols = iwImg.Col();

    // KImageColor 객체 생성 (크기는 KImageWord와 동일)
    KImageColor colorImage(rows, cols);

    // 각 라벨에 고유한 RGB 값을 부여하는 함수 (단순히 예시로 만든 함수)
    auto getRGBForLabel = [](int label) {
        // 라벨 값이 0이면 배경, 0이 아니면 고유 색상 할당
        if (label == 0) {
            return std::make_tuple(0, 0, 0); // 배경은 검정색
        }

        // 고유한 RGB 값을 만들기 위한 방법
        // 라벨 번호에 따라 고유의 RGB 값을 만들기 위해 단순한 규칙 사용
        int r = (label * 53) % 256;
        int g = (label * 97) % 256;
        int b = (label * 139) % 256;

        return std::make_tuple(r, g, b);
    };

    // KImageWord의 각 라벨 값을 0~65535에서 고유한 RGB 색상으로 변환하여 KImageColor로 변환
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // KImageWord에서 픽셀 값(라벨 값) 가져오기
            int wordValue = iwImg._ppA[i][j];

            // 라벨 값에 따른 RGB 색상 얻기
            int r, g, b;
            std::tie(r, g, b) = getRGBForLabel(wordValue);

            // KImageColor에 변환된 RGB 값 저장
            colorImage._ppA[i][j].r = r;
            colorImage._ppA[i][j].g = g;
            colorImage._ppA[i][j].b = b;
        }
    }

    return colorImage;
}

using KBlob = std::vector<KPOINT>;
using KBlobList = std::vector<KBlob*>;

// Equivalence table 선언
std::unordered_map<int, int> equivalenceTable;

int findRoot(int label) {
    // 라벨의 루트를 찾는 함수 (경로 압축 방식으로 최적화 가능)
    while (equivalenceTable[label] != label) {
        equivalenceTable[label] = equivalenceTable[equivalenceTable[label]]; // 경로 압축
        label = equivalenceTable[label];
    }
    return label;
}

void unionLabels(int label1, int label2) {
    // 두 라벨을 병합하는 함수
    int root1 = findRoot(label1);
    int root2 = findRoot(label2);
    if (root1 != root2) {
        equivalenceTable[root2] = root1; // root2를 root1으로 병합
    }
}

void MainFrame::on_pushLabeling_clicked()
{
    // 포커스된 이진 이미지 가져오기
    KImageGray igBin = _q_pFormFocused->ImageGray();

    // 이진 이미지를 복사해서 라벨링에 사용할 색상 이미지 생성
    KImageWord iwColor(igBin.Row(), igBin.Col());

    // 라벨을 저장할 블랍 리스트와 라벨 수 초기화
    KBlobList lBlobList;

    // 이웃을 선택할 수 있는 변수 (4-N 또는 8-N)
    int neighborType = ui->comboBoxNeighborType->currentIndex(); // 0: 4-N, 1: 8-N

    // 4-N type일 때 first pass
    if(neighborType == 0){
        // 라벨링 시작
        for (int i = 1; i < igBin.Row() - 1; i++) {
            for (int j = 1; j < igBin.Col() - 1; j++) {
                int uCur = igBin._ppA[i][j]; // 현재 픽셀 값 (0: 배경, 255: 전경)

                if (uCur == 0) continue; // 배경인 경우 건너뛰기

                // 왼쪽과 위쪽 픽셀의 라벨 가져오기
                int wLeftColor = iwColor._ppA[i][j - 1];
                int wUpColor = iwColor._ppA[i - 1][j];

                // 새로운 라벨 할당
                if (wLeftColor == 0 && wUpColor == 0) {
                    // 새로운 Blob 생성
                    KBlob* opBlob = new KBlob();
                    lBlobList.push_back(opBlob);
                    iwColor._ppA[i][j] = lBlobList.size(); // 새로운 라벨 할당

                    // Equivalence table에 새로운 라벨 등록
                    equivalenceTable[lBlobList.size()] = lBlobList.size();
                }
                // 위쪽만 라벨이 존재할 때
                else if (wUpColor != 0 && wLeftColor == 0) {
                    iwColor._ppA[i][j] = wUpColor; // 위쪽 라벨 복사
                    lBlobList[wUpColor - 1]->push_back(KPOINT(j, i)); // Blob에 좌표 추가
                }
                // 왼쪽만 라벨이 존재할 때
                else if (wUpColor == 0 && wLeftColor != 0) {
                    iwColor._ppA[i][j] = wLeftColor; // 왼쪽 라벨 복사
                    lBlobList[wLeftColor - 1]->push_back(KPOINT(j, i)); // Blob에 좌표 추가
                }
                else {
                    // 위쪽과 왼쪽 픽셀이 같은 라벨을 가질 때
                    if (wLeftColor == wUpColor) {
                        iwColor._ppA[i][j] = wUpColor; // 위쪽 라벨 복사
                        lBlobList[wUpColor - 1]->push_back(KPOINT(j, i)); // Blob에 좌표 추가
                    }
                    // 위쪽과 왼쪽 픽셀이 서로 다른 라벨을 가질 때, equivalence 관계 기록
                    else {
                        iwColor._ppA[i][j] = wUpColor; // 위쪽 라벨 복사
                        lBlobList[wUpColor - 1]->push_back(KPOINT(j, i));
                        unionLabels(wUpColor, wLeftColor);  // 두 라벨을 병합
                    }
                }
            }
        }
    }
    // 8-N type일 때 first pass
    else{
        // 8-이웃에서 확인해야 할 모든 이웃의 좌표 (상하좌우 및 대각선)
        std::vector<std::pair<int, int>> neighbors = {
            {-1, -1}, {-1, 0}, {-1, 1}, // 왼쪽 위, 위, 오른쪽 위
            {0, -1}                   // 왼쪽
        };

        // 라벨링 시작
        for (int i = 1; i < igBin.Row() - 1; i++) {
            for (int j = 1; j < igBin.Col() - 1; j++) {
                int uCur = igBin._ppA[i][j]; // 현재 픽셀 값 (0: 배경, 255: 전경)

                if (uCur == 0) continue; // 배경인 경우 건너뛰기

                int minLabel = 0;
                std::vector<int> neighborLabels; // 이웃들의 라벨을 저장

                // 8-이웃을 순회하면서 라벨을 확인
                for (const auto& n : neighbors) {
                    int ni = i + n.first;
                    int nj = j + n.second;
                    int neighborLabel = iwColor._ppA[ni][nj];

                    if (neighborLabel > 0) {
                        neighborLabels.push_back(neighborLabel);
                        if (minLabel == 0 || neighborLabel < minLabel) {
                            minLabel = neighborLabel;
                        }
                    }
                }

                if (neighborLabels.empty()) {
                    // 새로운 라벨 할당 (이웃이 모두 배경일 때)
                    KBlob* opBlob = new KBlob();
                    lBlobList.push_back(opBlob);
                    iwColor._ppA[i][j] = lBlobList.size(); // 새로운 라벨 할당

                    // Equivalence table에 새로운 라벨 등록
                    equivalenceTable[lBlobList.size()] = lBlobList.size();
                } else {
                    // 이웃 중 가장 작은 라벨을 사용
                    iwColor._ppA[i][j] = minLabel;
                    lBlobList[minLabel - 1]->push_back(KPOINT(j, i)); // Blob에 좌표 추가

                    // 이웃들의 라벨을 equivalenceTable로 병합
                    for (int label : neighborLabels) {
                        unionLabels(minLabel, label);
                    }
                }
            }
        }
    }

    // second pass
    for (int i = 0; i < igBin.Row(); i++) {
        for (int j = 0; j < igBin.Col(); j++) {
            int label = iwColor._ppA[i][j];
            if (label > 0) {
                iwColor._ppA[i][j] = findRoot(label); // 루트 라벨로 통일
            }
        }
    }

    // 라벨 수 리스트 위젯에 표시
    ui->listWidget->clear();            // 기존 리스트 초기화
    int totalLabels = lBlobList.size(); // 총 라벨 수 계산
    QString labelInfo = QString("Number of labels: %1").arg(totalLabels); // 출력
    ui->listWidget->addItem(labelInfo); // 리스트에 추가

    // 라벨링된 이미지 출력
    KImageColor colorImage = ConvertToColor(iwColor);  // KImageWord를 KImageColor로 변환
    ImageForm* q_pForm = new ImageForm(colorImage, "Labeled Image", this);

    q_pForm->show();
    _lImageForm.push_back(q_pForm);

    // UI 갱신
    UpdateUI();
}
