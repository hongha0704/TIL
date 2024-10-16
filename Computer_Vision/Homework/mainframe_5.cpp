#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"
#include "edge.h"
#include "kfc.h"

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


// Homework5

// HistogramEQ
void MainFrame::on_pushHistogramEQ_clicked()
{
    // 입력 영상
    KImageGray igMain = _q_pFormFocused->ImageGray();

    // Histograming

    int nRow = igMain.Row();
    int nCol = igMain.Col();
    std::vector<double> dpHisto(256, 0);  // 크기 256으로 벡터 초기화

    // 히스토그램 계산
    for(int i = 0; i < nRow; i++)
        for(int j = 0; j < nCol; j++)
            dpHisto[igMain[i][j]]++;  // 히스토그램 값을 증가시킴

    // 파일에 저장
    std::ofstream fout("./output/hist_before.csv");
    for(unsigned int i = 0; i < dpHisto.size(); i++)
        fout << dpHisto[i] << ',';  // 히스토그램 값을 파일에 저장
    fout.close();

    // Histogram Equalization

    // 누적 히스토그램 계산 (accumulated histogram)
    for(unsigned int i = 1; i < dpHisto.size(); i++)
        dpHisto[i] += dpHisto[i - 1];  // 이전 값과 현재 값을 더해 누적 계산

    // 히스토그램 평활화 (Histogram Equalization)
    int totalPixels = nRow * nCol;
    for(unsigned int i = 0; i < dpHisto.size(); i++)
        dpHisto[i] = dpHisto[i] / (double)totalPixels;  // 누적 히스토그램을 정규화

    // 원본 이미지 변환 (transform the original image)
    for(int i = 0; i < nRow; i++)
        for (int j = 0; j < nCol; j++)
            // 정규화된 값을 255 스케일로 변환
            igMain[i][j] = (unsigned char)(dpHisto[igMain[i][j]] * 255.0 + 0.5);

    std::fill(dpHisto.begin(), dpHisto.end(), 0);  // dpHisto 값을 0으로 초기화
    for (int i = 0; i < nRow; i++)
        for (int j = 0; j < nCol; j++)
            dpHisto[igMain[i][j]]++;  // 재계산된 히스토그램 값 증가

    // 파일에 저장
    fout.open("./output/hist_after.csv");
    for(unsigned int i = 0; i < dpHisto.size(); i++)
        fout << dpHisto[i] << ',';  // 히스토그램 값을 파일에 저장
    fout.close();

    // 출력창 결정
    ImageForm* q_pForm = 0;
    for(auto item : _lImageForm)
        if(item->ID() == "Histogram Equalized" && item->size() == _q_pFormFocused->size())
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
        q_pForm = new ImageForm(igMain, "Histogram Equalized", this);
        q_pForm->show();
        _lImageForm.push_back(q_pForm);
    }

    // UI 활성화 갱신
    UpdateUI();
}


// HistogramMatching
void MainFrame::on_pushHistogramMatching_clicked()
{
    // 타겟 이미지 파일 선택
    QFileDialog::Options q_Options = QFileDialog::DontResolveSymlinks |
                                     QFileDialog::DontUseNativeDialog;
    QString              q_stFile  = QFileDialog::getOpenFileName(this,
                                                    tr("Select a Target Image"), "./data",
                                                    "Image Files(*.ppm *.pgm *.tif)", 0, q_Options);
    if(q_stFile.length() == 0)
        return;

    // 타겟 이미지 저장
    ImageForm* q_pFormT = new ImageForm(q_stFile, "Target Image", this);
    KImageColor icTarget = q_pFormT->ImageColor();
    _lImageForm.push_back(q_pFormT);
    q_pFormT->show();

    // 소스 이미지 파일 선택
    q_stFile = QFileDialog::getOpenFileName(this, tr("Select a Source Image"),
                                            "./data", "Image Files(*.ppm *.pgm *.tif)",
                                            0, q_Options);
    if(q_stFile.length() == 0)
        return;

    // 소스 이미지 저장
    ImageForm* q_pFormS = new ImageForm(q_stFile, "Source Image", this);
    KImageColor icSrc = q_pFormS->ImageColor();
    _lImageForm.push_back(q_pFormS);
    q_pFormS->show();

    // Histogram Matching

    // 컬러 채널 분리
    KImageGray igpTarget[3], igpSrc[3], igpMatched[3];
    icTarget.SplitInto(igpTarget[0], igpTarget[1], igpTarget[2]); // 0: Red, 1: Green, 2: Blue
    icSrc.SplitInto(igpSrc[0], igpSrc[1], igpSrc[2]);             // 0: Red, 1: Green, 2: Blue

    // 누적 히스토그램을 저장할 벡터
    std::vector<double> vpTargetC[3], vpSrcC[3];
    std::vector<int> npLookup(256);

    // 누적 히스토그램 생성
    for (int n = 0; n < 3; n++) {
        // 256 크기의 히스토그램 초기화
        vpTargetC[n].resize(256, 0.0);
        vpSrcC[n].resize(256, 0.0);

        // 히스토그램 계산 (타겟 이미지)
        std::vector<double> dpHistoTarget(256, 0.0);
        for(unsigned int i = 0; i < igpTarget[n].Row(); i++)
            for(unsigned int j = 0; j < igpTarget[n].Col(); j++)
                dpHistoTarget[igpTarget[n][i][j]]++;

        // 히스토그램 정규화 (타겟 이미지)
        for(unsigned int i = 0; i < 256; i++)
            dpHistoTarget[i] /= (double)(igpTarget[n].Size());

        // 누적 히스토그램 계산 (타겟 이미지)
        for (int i = 1; i < 256; i++)
            dpHistoTarget[i] += dpHistoTarget[i - 1];

        // 누적 히스토그램을 저장
        vpTargetC[n] = dpHistoTarget;

        // 히스토그램 계산 (원본 이미지)
        std::vector<double> dpHistoSrc(256, 0.0);
        for(unsigned int i = 0; i < igpSrc[n].Row(); i++)
            for(unsigned int j = 0; j < igpSrc[n].Col(); j++)
                dpHistoSrc[igpSrc[n][i][j]]++;

        // 히스토그램 정규화 (원본 이미지)
        for (int i = 0; i < 256; i++)
            dpHistoSrc[i] /= (double)(igpSrc[n].Size());

        // 누적 히스토그램 계산 (원본 이미지)
        for (int i = 1; i < 256; i++)
            dpHistoSrc[i] += dpHistoSrc[i - 1];

        // 누적 히스토그램을 저장
        vpSrcC[n] = dpHistoSrc;

        // 룩업 테이블 초기화
        npLookup.assign(256, 0);

        // 히스토그램 매칭을 위한 룩업 테이블 생성
        for (int i = 0; i < 256; i++) {
            if (vpSrcC[n][i] != 0.0) {
                // 타겟 이미지의 누적 히스토그램에서 원본 이미지의 값과 가장 가까운 값을 찾음
                auto it = std::lower_bound(vpTargetC[n].begin(), vpTargetC[n].end(), vpSrcC[n][i]);
                npLookup[i] = std::distance(vpTargetC[n].begin(), it);
            }
        }

        // 매칭된 이미지 생성
        igpMatched[n].Create(icSrc.Row(), icSrc.Col());
        for(unsigned int i = 0; i < igpSrc[n].Row(); i++)
            for(unsigned int j = 0; j < igpSrc[n].Col(); j++)
                igpMatched[n][i][j] = (unsigned char)(npLookup[igpSrc[n][i][j]]);
    }

    // 최종 출력 이미지 생성
    KImageColor icMatched;
    icMatched.FromRGB(igpMatched[_RED], igpMatched[_GREEN], igpMatched[_BLUE]);

    // 결과 표시
    ImageForm* q_pForm = new ImageForm(icMatched, "Histogram Matched", this);

    _lImageForm.push_back(q_pForm);
    q_pForm->show();
}
