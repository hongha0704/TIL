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
        ui->pushContrast->setEnabled(_q_pFormFocused && _q_pFormFocused->ID() == "OPEN");
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



void MainFrame::on_pushContrast_clicked()
{
    // 포커스 된 ImageForm으로부터 영상을 가져옴
    if(_q_pFormFocused == nullptr || _q_pFormFocused->ImageColor().Address() == nullptr || _q_pFormFocused->ID() != "OPEN")
        return;

    // 포커스 된 ImageForm의 컬러 영상을 가져옴
    KImageColor icImg = _q_pFormFocused->ImageColor();

    // 입력 대비 변환 범위 [a, b]와 출력 대비 변환 범위 [a', b'] 값 가져오기
    int a = ui->spinContrastA->value();
    int b = ui->spinContrastB->value();
    int a_prime = ui->spinContrastA_prime->value();
    int b_prime = ui->spinContrastB_prime->value();

    // 각 색상 채널(R, G, B)에 대해 선형 대비 변환 적용
    for(unsigned int y = 0; y < icImg.Row(); y++)
    {
        for(unsigned int x = 0; x < icImg.Col(); x++)
        {
            // 현재 픽셀의 R, G, B 값을 가져옴
            int R = icImg._ppA[y][x].r;
            int G = icImg._ppA[y][x].g;
            int B = icImg._ppA[y][x].b;

            // R 채널에 선형 대비 변환 적용
            R = (R - a) * (b_prime - a_prime) / (b - a) + a_prime;
            R = std::clamp(R, a_prime, b_prime);  // a', b' 범위로 클램프

            // G 채널에 선형 대비 변환 적용
            G = (G - a) * (b_prime - a_prime) / (b - a) + a_prime;
            G = std::clamp(G, a_prime, b_prime);  // a', b' 범위로 클램프

            // B 채널에 선형 대비 변환 적용
            B = (B - a) * (b_prime - a_prime) / (b - a) + a_prime;
            B = std::clamp(B, a_prime, b_prime);  // a', b' 범위로 클램프

            // 변환된 값으로 픽셀 수정
            icImg._ppA[y][x].r = R;
            icImg._ppA[y][x].g = G;
            icImg._ppA[y][x].b = B;
        }
    }

    // 출력창 결정
    ImageForm* q_pForm = nullptr;
    for(auto item : _lImageForm)
    {
        if(item->ID() == "Contrast Transform" && item->size() == _q_pFormFocused->size())
        {
            q_pForm = item;
            break;
        }
    }

    // 기존 창에 표시
    if(q_pForm)
    {
        q_pForm->Update(icImg);
    }
    // 새로운 창에 표시
    else
    {
        q_pForm = new ImageForm(icImg, "Contrast Transform", this);
        q_pForm->show();
        _lImageForm.push_back(q_pForm);
    }

    // UI 활성화 갱신
    UpdateUI();
}
