#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"

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
        ui->pushOstu->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "OPEN" && _q_pFormFocused->ImageGray().Address());
        ui->pushThresholding->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "OPEN" && _q_pFormFocused->ImageGray().Address());
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


// =========================================================================================================

// Thresholding
void MainFrame::on_pushOstu_clicked()
{
    // Ostu thresholding
    KImageGray igMain = _q_pFormFocused->ImageGray();
    KImageGray igBin;
    KBINARIZATION_OUTPUT* opBinOutput = KHisto().Ostu(&igMain, &igBin);

    // 출력창 결정
    // ImageForm* q_pForm = 0;
    // for(auto item : _lImageForm)
    //     if(item->ID() == "Binary Image" && item->size() == _q_pFormFocused->size())
    //     {
    //         q_pForm = item;
    //         break;
    //     }

    // // 기존 창에 표시
    // if(q_pForm)
    //     q_pForm->Update(igBin);
    // // 새로운 창에 표시
    // else
    // {
    //     q_pForm = new ImageForm(igBin, "Binary Image", this);
    //     q_pForm->show();
    //     _lImageForm.push_back(q_pForm);
    // }

    // Threshold 값 표시
    ui->spinOstu->setValue(opBinOutput->nThresh);
    ui->listWidget->addItem(QString(">> Ostu Threshold : %1").arg(opBinOutput->nThresh));
    ui->listWidget->show();

    // UI 활성화 갱신
    UpdateUI();
}


// Thresholding
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


// Histogram
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



// Homework4

// Opening
void MainFrame::on_pushOpening_clicked()
{
    // 포커스된 이진 이미지 가져오기
    KImageGray igBin = _q_pFormFocused->ImageGray();
    KImageGray igErode = _q_pFormFocused->ImageGray();
    KImageGray igOpening = _q_pFormFocused->ImageGray();

    // 커널 크기가 3X3일 때, Opening 연산 수행
    if(ui->radioButton3X3->isChecked())
    {
        // Erosion 연산
        for (unsigned int i = 1; i < igBin.Row() - 1; i++) {
            for (unsigned int j = 1; j < igBin.Col() - 1; j++) {
                if(igBin[i][j])
                    if(igBin[i-1][j-1]==0 || igBin[i-1][j]==0 || igBin[i-1][j+1]==0 || igBin[i][j-1]==0
                        || igBin[i][j+1]==0 || igBin[i+1][j-1]==0 || igBin[i+1][j]==0 || igBin[i+1][j+1]==0)

                igErode._ppA[i][j] = 0;
            }
        }
        igOpening = igErode;

        // Dilation 연산
        for (unsigned int i = 1; i < igErode.Row() - 1; i++) {
            for (unsigned int j = 1; j < igErode.Col() - 1; j++) {
                if(igErode[i][j] == 0)
                    if(igErode[i-1][j-1] || igErode[i-1][j] || igErode[i-1][j+1] || igErode[i][j-1]
                        || igErode[i][j+1] || igErode[i+1][j-1] || igErode[i+1][j] || igErode[i+1][j+1])

                igOpening._ppA[i][j] = 255;
            }
        }
    }

    // 커널 크기가 5X5일 때, Opening 연산 수행
    else if(ui->radioButton5X5->isChecked())
    {
        // Erosion 연산
        for (unsigned int i = 2; i < igBin.Row() - 2; i++) {
            for (unsigned int j = 2; j < igBin.Col() - 2; j++) {
                if(igBin[i][j])
                    if(igBin[i-2][j-2]==0 || igBin[i-2][j-1]==0 || igBin[i-2][j]==0 || igBin[i-2][j+1]==0 || igBin[i-2][j+2]==0 ||
                        igBin[i-1][j-2]==0 || igBin[i-1][j-1]==0 || igBin[i-1][j]==0 || igBin[i-1][j+1]==0 || igBin[i-1][j+2]==0 ||
                        igBin[i][j-2]==0   || igBin[i][j-1]==0   || igBin[i][j+1]==0   || igBin[i][j+2]==0 ||
                        igBin[i+1][j-2]==0 || igBin[i+1][j-1]==0 || igBin[i+1][j]==0 || igBin[i+1][j+1]==0 || igBin[i+1][j+2]==0 ||
                        igBin[i+2][j-2]==0 || igBin[i+2][j-1]==0 || igBin[i+2][j]==0 || igBin[i+2][j+1]==0 || igBin[i+2][j+2]==0)

                igErode._ppA[i][j] = 0;
            }
        }
        igOpening = igErode;

        // Dilation 연산
        for (unsigned int i = 2; i < igErode.Row() - 2; i++) {
            for (unsigned int j = 2; j < igErode.Col() - 2; j++) {
                if(igErode[i][j] == 0)
                    if(igErode[i-2][j-2] || igErode[i-2][j-1] || igErode[i-2][j] || igErode[i-2][j+1] || igErode[i-2][j+2] ||
                        igErode[i-1][j-2] || igErode[i-1][j-1] || igErode[i-1][j] || igErode[i-1][j+1] || igErode[i-1][j+2] ||
                        igErode[i][j-2]   || igErode[i][j-1]   || igErode[i][j+1]   || igErode[i][j+2] ||
                        igErode[i+1][j-2] || igErode[i+1][j-1] || igErode[i+1][j] || igErode[i+1][j+1] || igErode[i+1][j+2] ||
                        igErode[i+2][j-2] || igErode[i+2][j-1] || igErode[i+2][j] || igErode[i+2][j+1] || igErode[i+2][j+2])

                igOpening._ppA[i][j] = 255;
            }
        }
    }

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
        q_pForm->Update(igOpening);
    // 새로운 창에 표시
    else
    {
        q_pForm = new ImageForm(igOpening, "Opening", this);
        q_pForm->show();
        _lImageForm.push_back(q_pForm);
    }

    // UI 활성화 갱신
    UpdateUI();
}


// Closing
void MainFrame::on_pushClosing_clicked()
{
    // 포커스된 이진 이미지 가져오기
    KImageGray igBin = _q_pFormFocused->ImageGray();
    KImageGray igDilate = _q_pFormFocused->ImageGray();
    KImageGray igClosing = _q_pFormFocused->ImageGray();

    // 커널 크기가 3X3일 때, Closing 연산 수행
    if(ui->radioButton3X3_2->isChecked())
    {
        // Dilation 연산
        for (unsigned int i = 1; i < igBin.Row() - 1; i++) {
            for (unsigned int j = 1; j < igBin.Col() - 1; j++) {
                if(igBin[i][j] == 0)
                    if(igBin[i-1][j-1] || igBin[i-1][j] || igBin[i-1][j+1] || igBin[i][j-1]
                        || igBin[i][j+1] || igBin[i+1][j-1] || igBin[i+1][j] || igBin[i+1][j+1])

                igDilate._ppA[i][j] = 255;
            }
        }
        igClosing = igDilate;

        // Erosion 연산
        for (unsigned int i = 1; i < igDilate.Row() - 1; i++) {
            for (unsigned int j = 1; j < igDilate.Col() - 1; j++) {
                if(igDilate[i][j])
                    if(igDilate[i-1][j-1]==0 || igDilate[i-1][j]==0 || igDilate[i-1][j+1]==0 || igDilate[i][j-1]==0
                        || igDilate[i][j+1]==0 || igDilate[i+1][j-1]==0 || igDilate[i+1][j]==0 || igDilate[i+1][j+1]==0)

                igClosing._ppA[i][j] = 0;
            }
        }
    }

    // 커널 크기가 5X5일 때, Opening 연산 수행
    else if(ui->radioButton5X5_2->isChecked())
    {
        // Dilation 연산
        for (unsigned int i = 2; i < igBin.Row() - 2; i++) {
            for (unsigned int j = 2; j < igBin.Col() - 2; j++) {
                if(igBin[i][j] == 0)
                    if(igBin[i-2][j-2] || igBin[i-2][j-1] || igBin[i-2][j] || igBin[i-2][j+1] || igBin[i-2][j+2] ||
                        igBin[i-1][j-2] || igBin[i-1][j-1] || igBin[i-1][j] || igBin[i-1][j+1] || igBin[i-1][j+2] ||
                        igBin[i][j-2]   || igBin[i][j-1]   || igBin[i][j+1]   || igBin[i][j+2] ||
                        igBin[i+1][j-2] || igBin[i+1][j-1] || igBin[i+1][j] || igBin[i+1][j+1] || igBin[i+1][j+2] ||
                        igBin[i+2][j-2] || igBin[i+2][j-1] || igBin[i+2][j] || igBin[i+2][j+1] || igBin[i+2][j+2])

                igDilate._ppA[i][j] = 255;
            }
        }
        igClosing = igDilate;

        // Erosion 연산
        for (unsigned int i = 2; i < igDilate.Row() - 2; i++) {
            for (unsigned int j = 2; j < igDilate.Col() - 2; j++) {
                if(igDilate[i][j])
                    if(igDilate[i-2][j-2]==0 || igDilate[i-2][j-1]==0 || igDilate[i-2][j]==0 || igDilate[i-2][j+1]==0 || igDilate[i-2][j+2]==0 ||
                        igDilate[i-1][j-2]==0 || igDilate[i-1][j-1]==0 || igDilate[i-1][j]==0 || igDilate[i-1][j+1]==0 || igDilate[i-1][j+2]==0 ||
                        igDilate[i][j-2]==0   || igDilate[i][j-1]==0   || igDilate[i][j+1]==0   || igDilate[i][j+2]==0 ||
                        igDilate[i+1][j-2]==0 || igDilate[i+1][j-1]==0 || igDilate[i+1][j]==0 || igDilate[i+1][j+1]==0 || igDilate[i+1][j+2]==0 ||
                        igDilate[i+2][j-2]==0 || igDilate[i+2][j-1]==0 || igDilate[i+2][j]==0 || igDilate[i+2][j+1]==0 || igDilate[i+2][j+2]==0)

                igClosing._ppA[i][j] = 0;
            }
        }
    }

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
        q_pForm->Update(igClosing);
    // 새로운 창에 표시
    else
    {
        q_pForm = new ImageForm(igClosing, "Closing", this);
        q_pForm->show();
        _lImageForm.push_back(q_pForm);
    }

    // UI 활성화 갱신
    UpdateUI();
}


// Boundary Extraction
void MainFrame::on_pushButtonBoundaryExtraction_clicked()
{
    // 포커스된 이진 이미지 가져오기
    KImageGray igBin = _q_pFormFocused->ImageGray();
    KImageGray igBoundary = _q_pFormFocused->ImageGray();
    KImageGray igDilate = igBin.BinaryDilate(_WHITE);
    KImageGray igErode = igBin.BinaryErode(_WHITE);

    // Boundary Extraction (neighborhood mask, boundary type select)

    // 4-neighborhood mask / foreground
    if(ui->radioButtonB4->isChecked() && ui->radioButtonForeground->isChecked()){
        for (unsigned int i = 1; i < igBin.Row() - 1; i++) {
            for (unsigned int j = 1; j < igBin.Col() - 1; j++) {
                // 픽셀값이 1일 때
                if(igBin[i][j])
                    // 이웃 중 하나라도 배경이 있다면 경계로 인식, 아니라면 픽셀값을 0으로 변경
                    if(!(igBin[i-1][j]==0 || igBin[i][j-1]==0 || igBin[i][j+1]==0 || igBin[i+1][j]==0))
                        igBoundary._ppA[i][j] = 0;
            }
        }
    }

    // 8-neighborhood mask / foreground
    else if(ui->radioButtonB8->isChecked() && ui->radioButtonForeground->isChecked()){
        for (unsigned int i = 1; i < igBin.Row() - 1; i++) {
            for (unsigned int j = 1; j < igBin.Col() - 1; j++) {
                // 픽셀값이 1일 때
                if(igBin[i][j])
                    // 이웃 중 하나라도 배경이 있다면 경계로 인식, 아니라면 픽셀값을 0으로 변경
                    if(!(igBin[i-1][j-1]==0 || igBin[i-1][j]==0 || igBin[i-1][j+1]==0 || igBin[i][j-1]==0
                          || igBin[i][j+1]==0 || igBin[i+1][j-1]==0 || igBin[i+1][j]==0 || igBin[i+1][j+1]==0))
                        igBoundary._ppA[i][j] = 0;
            }
        }
    }

    // 4-neighborhood mask / background
    else if(ui->radioButtonB4->isChecked() && ui->radioButtonBackground->isChecked()){
        igBoundary = igDilate;
        // Boundary Extration
        for(unsigned int i=1; i<igDilate.Row() - 1; i++){
            for(unsigned int j=1; j<igDilate.Col() - 1; j++){
                // 픽셀값이 1일 때
                if(igDilate[i][j])
                    // 이웃 중 하나라도 배경이 있다면 경계로 인식, 아니라면 픽셀값을 0으로 변경
                    if(!(igDilate[i-1][j]==0 || igDilate[i][j-1]==0 || igDilate[i][j+1]==0 || igDilate[i+1][j]==0))
                        igBoundary._ppA[i][j] = 0;
            }
        }
    }

    // 8-neighborhood mask / background
    else if(ui->radioButtonB8->isChecked() && ui->radioButtonBackground->isChecked()){
        igBoundary = igDilate;
        // Boundary Extration
        for(unsigned int i=1; i<igDilate.Row() - 1; i++){
            for(unsigned int j=1; j<igDilate.Col() - 1; j++){
                // 픽셀값이 1일 때
                if(igDilate[i][j])
                    // 이웃 중 하나라도 배경이 있다면 경계로 인식, 아니라면 픽셀값을 0으로 변경
                    if(!(igDilate[i-1][j-1]==0 || igDilate[i-1][j]==0 || igDilate[i-1][j+1]==0 || igDilate[i][j-1]==0
                          || igDilate[i][j+1]==0 || igDilate[i+1][j-1]==0 || igDilate[i+1][j]==0 || igDilate[i+1][j+1]==0))
                        igBoundary._ppA[i][j] = 0;
            }
        }
    }

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
        q_pForm->Update(igBoundary);
    // 새로운 창에 표시
    else
    {
        q_pForm = new ImageForm(igBoundary, "Boundary Extraction", this);
        q_pForm->show();
        _lImageForm.push_back(q_pForm);
    }

    // UI 활성화 갱신
    UpdateUI();
}

