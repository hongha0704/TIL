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
        ui->pushRGB2HSI->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "OPEN");
        ui->pushRGB2NRG->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "OPEN");
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



// Homework1

void MainFrame::on_pushRGB2HSI_clicked()
{
    // 포커스된 ImageForm으로부터 영상을 가져옴
    KImageColor icMain;
    if (_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address()
        && _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    // Hue, Saturation, Intensity 컴포넌트 이미지 생성
    KImageGray igHue(icMain.Row(), icMain.Col());
    KImageGray igSaturation(icMain.Row(), icMain.Col());
    KImageGray igIntensity(icMain.Row(), icMain.Col());

    // 각 픽셀을 반복하면서 RGB를 HSI로 변환
    for (unsigned int y = 0; y < icMain.Row(); y++) {
        for (unsigned int x = 0; x < icMain.Col(); x++) {
            // 각 픽셀의 RGB 값을 0-255에서 0-1 사이의 범위로 정규화
            float r = icMain._ppA[y][x].r / 255.0;
            float g = icMain._ppA[y][x].g / 255.0;
            float b = icMain._ppA[y][x].b / 255.0;

            // 해당 픽셀의 RGB 값 중 최대값과 최소값을 계산
            float maxRGB = std::max({r, g, b});
            float minRGB = std::min({r, g, b});
            float delta = maxRGB - minRGB;

            // Hue 계산
            float hue = 0.0;
            if (delta != 0) {
                if (maxRGB == r)
                    hue = 60 * ((g - b) / delta);
                else if (maxRGB == g)
                    hue = 60 * ((b - r) / delta + 2);
                else if (maxRGB == b)
                    hue = 60 * ((r - g) / delta + 4);

                if (hue < 0)
                    hue += 360;
            }

            // Saturation 계산
            float saturation = (maxRGB == 0) ? 0 : (delta / maxRGB);

            // Intensity (Value) 계산
            float intensity = maxRGB;

            // 값들을 0-255 범위로 매핑하여 디스플레이
            igHue._ppA[y][x] = (unsigned char)((hue / 360.0) * 255.0);
            igSaturation._ppA[y][x] = (unsigned char)(saturation * 255.0);
            igIntensity._ppA[y][x] = (unsigned char)(intensity * 255.0);
        }
    }

    // 각 컴포넌트에 대한 ImageForm 생성 및 디스플레이
    ImageForm* q_pHueForm = new ImageForm(igHue, "Hue Image", this);
    _lImageForm.push_back(q_pHueForm);
    q_pHueForm->show();

    ImageForm* q_pSaturationForm = new ImageForm(igSaturation, "Saturation Image", this);
    _lImageForm.push_back(q_pSaturationForm);
    q_pSaturationForm->show();

    ImageForm* q_pIntensityForm = new ImageForm(igIntensity, "Intensity Image", this);
    _lImageForm.push_back(q_pIntensityForm);
    q_pIntensityForm->show();
}


void MainFrame::on_pushRGB2NRG_clicked()
{
    // 포커스된 ImageForm으로부터 영상을 가져옴
    KImageColor icMain;
    if (_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address()
        && _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    // 정규화된 빨간색과 초록색 컴포넌트 이미지 생성
    KImageGray igNormalizedRed(icMain.Row(), icMain.Col());
    KImageGray igNormalizedGreen(icMain.Row(), icMain.Col());

    // 각 픽셀을 반복하면서 RGB를 NRG로 변환
    for (unsigned int y = 0; y < icMain.Row(); y++) {
        for (unsigned int x = 0; x < icMain.Col(); x++) {
            float r = icMain._ppA[y][x].r;
            float g = icMain._ppA[y][x].g;
            float b = icMain._ppA[y][x].b;
            float sum = r + g + b + 0.0001; // 0으로 나누는 것을 방지

            // 빨간색과 초록색을 정규화
            float normalizedRed = r / sum;
            float normalizedGreen = g / sum;

            // 정규화된 값을 0-255 범위로 매핑하여 디스플레이
            igNormalizedRed._ppA[y][x] = (unsigned char)(normalizedRed * 255.0);
            igNormalizedGreen._ppA[y][x] = (unsigned char)(normalizedGreen * 255.0);
        }
    }

    // 각 컴포넌트에 대한 ImageForm 생성 및 디스플레이
    ImageForm* q_pRedForm = new ImageForm(igNormalizedRed, "Normalized Red Image", this);
    _lImageForm.push_back(q_pRedForm);
    q_pRedForm->show();

    ImageForm* q_pGreenForm = new ImageForm(igNormalizedGreen, "Normalized Green Image", this);
    _lImageForm.push_back(q_pGreenForm);
    q_pGreenForm->show();
}

