#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"termios.h"
#include"QFile"
#include"QTextStream"
#include"qdebug.h"
#include <fcntl.h>    /* For O_RDWR */
#include <unistd.h>
#include<qmessagebox.h>
#include<QDateTime>
#include<QTimer>
 #include <QTime>
#include<QMutex>
#include<QFile>
#include<QIODevice>
#include<QTextStream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<QDir>
QMutex loc;

QFile file;

int fd;

unsigned char search[12] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF,0x01,0x00,0x03,0x011,0x00,0x15};
unsigned char enroll[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x01,0x00,0x05};
unsigned char generate_ch[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x01,0x00,0x08};	//ok
unsigned char generate_ch1[13]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x04,0x02,0x02,0x00,0x09};	//ok
unsigned char un_cmd[12]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x03,0x05,0x00,0x09 };


unsigned char store[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x01,0x00,0x01,0x00,0x0F};			//ok
unsigned char store1[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x01,0x00,0x02,0x00,0x10};			//ok
unsigned char store2[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x01,0x00,0x03,0x00,0x11};			//ok
unsigned char store3[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x01,0x00,0x04,0x00,0x12};			//ok
unsigned char store4[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x01,0x00,0x05,0x00,0x13};			//ok
unsigned char store5[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x01,0x00,0x06,0x00,0x14};			//ok
unsigned char store6[15]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x06,0x06,0x01,0x00,0x07,0x00,0x15};			//ok

unsigned char identify[17]={0xef,0x01,0xff,0xff,0xff,0xff,0x01,0x00,0x08,0x1b,0x01,0x00,0x00,0x01,0x01,0x00,0x27};
unsigned char readtemp[16];

int list[10] = {1, 2, 3, 4, 5, 6,7,8,9};
QString input,str0;

FILE *returnfile,*ret;
int set;
char rtFile[80] ;
static int i=1;
int ms,h=9;

bool num1 = false;
bool num2 = false;
bool num3 = false;
bool num4 = false;
bool num5 = false;
bool num6 = false;

QTextStream out1;
QTime intime(h, 0, 0);
QTime out1Time(16,0,0);
QTime sss(1,0,0);
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //qDebug()<<intime+sss;

    fd = ::open("/dev/ttyUSB0", O_RDWR | O_NONBLOCK);
    struct termios oldtio,newtio;
    //struct termios tio;
    tcgetattr(fd,&oldtio); /* save current port settings */
    bzero(&newtio, sizeof(newtio));
    newtio.c_cflag = CLOCAL | CREAD | B9600 | CS8;
    newtio.c_cflag &= ~PARENB;
    newtio.c_cflag &= ~PARODD;
    newtio.c_cflag &= ~CSTOPB;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VMIN] = 0;
    newtio.c_cc[VTIME] = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd,TCSANOW,&newtio);
    printf ("pid 1 :- %d\n",fd);


QTimer *time = new QTimer();
connect(time,SIGNAL(timeout()),this,SLOT(repat()));
time->start(1000);



}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_register_2_clicked()
{

        loc.lock();
    ui->lineEdit->setText("  ");
    ui->status->setText("   ");
    loc.unlock();

           qDebug()<<list[1];


          if(i)
          {
              ui->lineEdit->setText("   ");
              ui->status->setText("   ");
           write(fd,enroll,12);
           sleep(1);
           read(fd,readtemp,12);
           sleep(1);
           qDebug()<<"enroll 1"<<readtemp[0];
           qDebug()<<"enroll 2"<<readtemp[1];
           qDebug()<<"enroll 3"<<readtemp[2];
           qDebug()<<"enroll 4"<<readtemp[3];
           qDebug()<<"enroll 5"<<readtemp[4];
           qDebug()<<"enroll 6"<<readtemp[5];
           qDebug()<<"enroll 7"<<readtemp[6];
           qDebug()<<"enroll 8"<<readtemp[7];
           qDebug()<<"enroll 9"<<readtemp[8];
           qDebug()<<"enroll 10"<<readtemp[9];
           qDebug()<<"enroll 11"<<readtemp[10];
           qDebug()<<"enroll 12\n"<<readtemp[11];

              if(readtemp[9] == 0)
              {
                  ui->lineEdit->setText(" ");
                  ui->status->setText(" ");
               write(fd,generate_ch,13);
               sleep(1);
               read(fd,readtemp,12);
               sleep(1);
               qDebug()<<"generate char 1"<<readtemp[0];
               qDebug()<<"generate char 2"<<readtemp[1];
               qDebug()<<"generate char 3"<<readtemp[2];
               qDebug()<<"generate char 4"<<readtemp[3];
               qDebug()<<"generate char 5"<<readtemp[4];
               qDebug()<<"generate char 6"<<readtemp[5];
               qDebug()<<"generate char 7"<<readtemp[6];
               qDebug()<<"generate char 8"<<readtemp[7];
               qDebug()<<"generate char 9"<<readtemp[8];
               qDebug()<<"generate char 10"<<readtemp[9];
               qDebug()<<"generate char 11"<<readtemp[10];
               qDebug()<<"generate char 12\n"<<readtemp[11];
                        if(readtemp[9]==0)
                        {

                         write(fd,enroll,12);
                         sleep(1);
                         read(fd,readtemp,12);
                         sleep(1);

                         qDebug()<<"enroll 1"<<readtemp[0];
                         qDebug()<<"enroll 2"<<readtemp[1];
                         qDebug()<<"enroll 3"<<readtemp[2];
                         qDebug()<<"enroll 4"<<readtemp[3];
                         qDebug()<<"enroll 5"<<readtemp[4];
                         qDebug()<<"enroll 6"<<readtemp[5];
                         qDebug()<<"enroll 7"<<readtemp[6];
                         qDebug()<<"enroll 8"<<readtemp[7];
                         qDebug()<<"enroll 9"<<readtemp[8];
                         qDebug()<<"enroll 10"<<readtemp[9];
                         qDebug()<<"enroll 11"<<readtemp[10];
                         qDebug()<<"enroll 12\n"<<readtemp[11];

                                    if(readtemp[9]==0)
                                    {
                                      ui->status->setText("plze take your finger");
                                      write(fd,generate_ch1,13);
                                      sleep(1);
                                      read(fd,readtemp,12);
                                      sleep(1);

                                       qDebug()<<"generate1 char 1"<<readtemp[0];
                                       qDebug()<<"generate1 char 2"<<readtemp[1];
                                       qDebug()<<"generate1 char 3"<<readtemp[2];
                                       qDebug()<<"generate1 char 4"<<readtemp[3];
                                       qDebug()<<"generate1 char 5"<<readtemp[4];
                                       qDebug()<<"generate1 char 6"<<readtemp[5];
                                       qDebug()<<"generate1 char 7"<<readtemp[6];
                                       qDebug()<<"generate1 char 8"<<readtemp[7];
                                       qDebug()<<"generate1 char 9"<<readtemp[8];
                                       qDebug()<<"generate1 char 10"<<readtemp[9];
                                       qDebug()<<"generate1 char 11"<<readtemp[10];
                                       qDebug()<<"generate1 char 12\n"<<readtemp[11];

                                                    if(readtemp[9] == 0)
                                                    {
                                                        write(fd,un_cmd,12);
                                                        sleep(1);
                                                        read(fd,readtemp,12);
                                                        sleep(1);
                                                        qDebug()<<"unknow 1"<<readtemp[0];
                                                        qDebug()<<"unknow 2"<<readtemp[1];
                                                        qDebug()<<"unknow 3"<<readtemp[2];
                                                        qDebug()<<"unknow 4"<<readtemp[3];
                                                        qDebug()<<"unknow 5"<<readtemp[4];
                                                        qDebug()<<"unknow 6"<<readtemp[5];
                                                        qDebug()<<"unknow 7"<<readtemp[6];
                                                        qDebug()<<"unknow 8"<<readtemp[7];
                                                        qDebug()<<"unknow 9"<<readtemp[8];
                                                        qDebug()<<"unknow 10"<<readtemp[9];
                                                        qDebug()<<"unknow 11"<<readtemp[10];
                                                        qDebug()<<"unknow 12\n"<<readtemp[11];
                                                        if(readtemp[9] == 0)
                                                        {
                                                            if(i==1)
                                                            {
                                                            write(fd,store1,15);
                                                            ui->lineEdit->setText("1");

                                                            }
                                                            else if(i==2)
                                                            {
                                                                ui->lineEdit->setText("2");
                                                                write(fd,store2,15);
                                                            }
                                                            else if(i==3)
                                                            {
                                                                write(fd,store3,15);
                                                                ui->lineEdit->setText("3");
                                                            }
                                                            else if(i==4)
                                                            {
                                                             ui->lineEdit->setText("4");
                                                                write(fd,store4,15);
                                                            }
                                                            else if(i==5)
                                                            {
                                                                write(fd,store5,15);
                                                                ui->lineEdit->setText("5");
                                                            }
                                                            else if(i==6)
                                                            {
                                                                write(fd,store6,15);
                                                                ui->lineEdit->setText("6");
                                                            }
                                                            else
                                                            {
                                                              //  i = 1;
                                                                ui->lineEdit->setText("Limt has done");


                                                            }
                                                            qDebug()<< "i value is " << i;
                                                          sleep(1);
                                                          read(fd,readtemp,12);
                                                          sleep(1);
                                                          qDebug()<<"store 1"<<readtemp[0];
                                                          qDebug()<<"store  2"<<readtemp[1];
                                                          qDebug()<<"store  3"<<readtemp[2];
                                                          qDebug()<<"store  4"<<readtemp[3];
                                                          qDebug()<<"store  5"<<readtemp[4];
                                                          qDebug()<<"store  6"<<readtemp[5];
                                                          qDebug()<<"store  7"<<readtemp[6];
                                                          qDebug()<<"store  8"<<readtemp[7];
                                                          qDebug()<<"store  9"<<readtemp[8];
                                                          qDebug()<<"store  10"<<readtemp[9];
                                                          qDebug()<<"store  11"<<readtemp[10];
                                                          qDebug()<<"store  12\n"<<readtemp[11];
                                                          i++;
                                                          ui->status->setText("registration success");

                                                         }
                                                         else
                                                         {
                                                         QMessageBox::warning(this, tr("Message"),tr("registration faild try gain"),QMessageBox::Ok);

                                                          }
                                                    }
                                                    else
                                                    {
                                                        QMessageBox::warning(this, tr("Message"),tr("registration faild try gain"),QMessageBox::Ok);

                                                    }
                                         }

                                         else
                                         {
                                            QMessageBox::warning(this, tr("Message"),tr("Plze Dont remove your finger "),QMessageBox::Ok);
                                           }


                     }
                     else
                     {

                     QMessageBox::warning(this, tr("Message"),tr("registration faild try gain"),QMessageBox::Ok);

                      }
              }
                else
                {
               int ret = QMessageBox::warning(this, tr("Message"),
                                              tr("Place your Finger and\n"
                                                 "Try again"),
                                              QMessageBox::Ok);
               qDebug()<<"place your finger" << ret;
                 }
}

}
bool entry1 = true;
bool entry2 = true;
bool entry3 = true;
bool entry4= true;
bool entry5 = true;


void MainWindow::on_pushButton_2_clicked()
{
    QString fname("data.csv");

  QFile  file(fname);

    if(file.open(QIODevice::Append))
    {
     QTextStream    out1(&file);



    ui->status_2->setText(" ");

    QTime verify = QTime::currentTime();

    qDebug()<<verify;
    qDebug()<<intime;
            if(verify >= out1Time)
            {
                qDebug()<<"log out1 time"<<out1Time;

                write(fd,enroll,12);
                sleep(1);
                 read(fd,readtemp,16);
                 sleep(1);
                  write(fd,generate_ch,13);
                   sleep(1);
                    read(fd,readtemp,16);
                    sleep(1);
                    write(fd,identify,17);
                   sleep(1);
                      read(fd,readtemp,16);
                    sleep(1);
            qDebug()<<"enroll 1"<<readtemp[0];
            qDebug()<<"enroll 2"<<readtemp[1];
            qDebug()<<"enroll 3"<<readtemp[2];
            qDebug()<<"enroll 4"<<readtemp[3];
            qDebug()<<"enroll 5"<<readtemp[4];
            qDebug()<<"enroll 6"<<readtemp[5];
            qDebug()<<"enroll 7"<<readtemp[6];
            qDebug()<<"enroll 8"<<readtemp[7];
            qDebug()<<"enroll 9"<<readtemp[8];
            qDebug()<<"enroll 10"<<readtemp[9];
            qDebug()<<"enroll 11"<<readtemp[10];
            qDebug()<<"enroll 12"<<readtemp[11];
            qDebug()<<"enroll 13"<<readtemp[12];
            qDebug()<<"enroll 14"<<readtemp[13];
            qDebug()<<"enroll 15"<<readtemp[14];
            qDebug()<<"enroll 16\n"<<readtemp[15];
            if(readtemp[9] == 0)
            {
            if(readtemp[11] == 2)
            {


                if(num1)
                {
                ui->status_2->setText(QString::number(list[0])+" logout  sucess");
                qDebug()<<"finger 1";
                num1 = false;
               QDateTime dateTime = QDateTime::currentDateTime();
               QString dateTimeString = dateTime.toString();
               ui->date->setText("Date and Time: " + dateTimeString);
               out1 << "log out1 at  "  << dateTimeString << " id " << list[0] << "\n";

                }
                else
                    ui->status_2->setText("No login Details found");


            }
            else if(readtemp[11]==3)
            {


                if(num2)
                {
                ui->status_2->setText(QString::number(list[1])+" logout  sucess");
                qDebug()<<"finger 2";
                num2 = false;
                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);
                out1 << "log out1 at  " << dateTimeString << " id " << list[1]<< "\n";

                }
                else
                    ui->status_2->setText("No login Details found");

            }
            else if(readtemp[11] == 4)
            {


                if(num3)
                {
                ui->status_2->setText(QString::number(list[2])+" logout  sucess");
                qDebug()<<"finger 1";
                num3= false;
                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);

                out1 << "log out1 at  " << dateTimeString << " id " << list[2]<< "\n";

                }
                else
                    ui->status_2->setText("No login Details found");

            }
            else if(readtemp[11] == 5)
            {


                if(num4)
                {
                ui->status_2->setText(QString::number(list[3])+" logout  sucess");
                qDebug()<<"finger 3";
                num4 = false;
                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);
                out1 << "log out1 at  " << dateTimeString << " id " << list[3]<< "\n";

                }
                else
                    ui->status_2->setText("No login Details found");

            }
            else if(readtemp[11] == 6)
            {

                if(num5)
                {
                ui->status_2->setText(QString::number(list[4])+" logout  sucess");
                qDebug()<<"finger 4";
                num5 = false;
                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);
                out1 << "log out1 at  " << dateTimeString << " id " << list[4]<< "\n";

                }
                else
                    ui->status_2->setText("No login Details found");

            }

}
            else
                ui->status_2->setText("place your finger and \n try agin");
            }

            else if(verify >= intime) // at login time checking
            {
                qDebug()<<"log in time time"<<intime;

                bool entry1 = true;
                bool entry2 = true;
                bool entry3 = true;
                bool entry4= true;
                bool entry5 = true;

                write(fd,enroll,12);
                sleep(1);
                 read(fd,readtemp,16);
                 sleep(1);
                  write(fd,generate_ch,13);
                   sleep(1);
                    read(fd,readtemp,16);
                    sleep(1);
                    write(fd,identify,17);
                   sleep(1);
                      read(fd,readtemp,16);
                    sleep(1);
            qDebug()<<"enroll 1"<<readtemp[0];
            qDebug()<<"enroll 2"<<readtemp[1];
            qDebug()<<"enroll 3"<<readtemp[2];
            qDebug()<<"enroll 4"<<readtemp[3];
            qDebug()<<"enroll 5"<<readtemp[4];
            qDebug()<<"enroll 6"<<readtemp[5];
            qDebug()<<"enroll 7"<<readtemp[6];
            qDebug()<<"enroll 8"<<readtemp[7];
            qDebug()<<"enroll 9"<<readtemp[8];
            qDebug()<<"enroll 10"<<readtemp[9];
            qDebug()<<"enroll 11"<<readtemp[10];
            qDebug()<<"enroll 12"<<readtemp[11];
            qDebug()<<"enroll 13"<<readtemp[12];
            qDebug()<<"enroll 14"<<readtemp[13];
            qDebug()<<"enroll 15"<<readtemp[14];
            qDebug()<<"enroll 16\n"<<readtemp[15];
            if(readtemp[9]==0)
            {
            if(readtemp[11] == 2)
            {


                if(entry1)
                {
                    num1 = true;
                ui->status_2->setText(QString::number(list[0])+" login  sucess");
                qDebug()<<"finger 1";

               QDateTime dateTime = QDateTime::currentDateTime();
               QString dateTimeString = dateTime.toString();
               ui->date->setText("Date and Time: " + dateTimeString);
               out1 << "log in at  " << dateTimeString << " id " << list[0]<< "\n";

                }


            }
            else if(readtemp[11]==3)
            {


                if(entry2)
                {
                    num2 = true;
                ui->status_2->setText(QString::number(list[1])+" login  sucess");
                qDebug()<<"finger 2";

                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);
                out1 << "log in at  " << dateTimeString << " id " << list[1]<< "\n";

                }

            }
            else if(readtemp[11] == 4)
            {


                if(entry3)
                {
                    num3=true;
                ui->status_2->setText(QString::number(list[2])+" login  sucess");
                qDebug()<<"finger 1";

                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);
                out1 << "log in at  " << dateTimeString << " id " << list[2]<< "\n";

                }

            }
            else if(readtemp[11] == 5)
            {


                if(entry4)
                {
                    num4 = true;
                ui->status_2->setText(QString::number(list[3])+" login  sucess");
                qDebug()<<"finger 3";

                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);
                out1 << "log in at  " << dateTimeString << " id " << list[3]<< "\n";

                }

            }
            else if(readtemp[11] == 6)
            {

                if(entry5)
                {
                    num5 = true;
                ui->status_2->setText(QString::number(list[4])+" login  sucess");
                qDebug()<<"finger 4";

                QDateTime dateTime = QDateTime::currentDateTime();
                QString dateTimeString = dateTime.toString();
                ui->date->setText(dateTimeString);
                out1 << "log in at  " << dateTimeString << " id " << list[4]<< "\n";

                }

            }
}
            else
            ui->status_2->setText("place your finger");
            }

}
}
int value;
void MainWindow::on_timeEdit_timeChanged(const QTime &time)
{
    intime = time;
}

void MainWindow::on_timeEdit_2_timeChanged(const QTime &time)
{
   out1Time = time;
}

void MainWindow::repat()
{

  //  returnfile =fopen("/var/www/html/data.txt","r") ;



    QFile file1("/var/www/html/index.txt");
    file1.open(QFile::WriteOnly);
    QTextStream out(&file1);

 /*   if(returnfile)
       {

        fscanf(returnfile,"%d",&value);

        qDebug()<<"the value is "<<value;


    }*/

     //  printf("Content-type: text/html\r\n\r\n,charset=iso-8859-1\",13,10") ;


out<<"<html> ";

out<<"<H1><B><U><P ALIGN=center><font size=\"40\" face=\"verdana\" color=\"AC0638\"> Online </font> </P></U></B></H1>";
out<<"<input ALIGN=center type=\"image\" src=\"cvr5.png\" NAME=\"install\"></br>";

//out <<"<?php error_reporting(0);if(isset($_GET['id'])){ 	$id = $_GET['id'];}if(isset($_GET['content'])){ $content = $_GET['content'];}?>";

//out << "<div>Control Switches <INPUT TYPE=\"Radio\" class = \"electric\" name=\"electric\" Value=\"1\" <?php echo (isset($id) && $id=='1')?'checked':'unchecked' ?> FAN ON <INPUT TYPE=\"Radio\" class = \"electric\" name=\"electric\" Value=\"2\" <?php echo (isset($id) && $id=='2')?'checked':'unchecked' ?> FAN OFF <INPUT TYPE=\"Radio\" class = \"electric\" name=\"electric\" Value=\"3\" <?php echo (isset($id) && $id=='3')?'checked':'unchecked' ?> LIGHT ON <INPUT TYPE=\"Radio\" class = \"electric\" name=\"electric\" Value=\"4\" <?php echo (isset($id) && $id=='4')?'checked':'unchecked' ?> LIGHT OFF";// <INPUT TYPE=\"Radio\" class = \"electric\" name=\"electric\" Value=\"5\" <?php echo (isset($id) && $id=='5')?'checked':'unchecked' ?> MOTOR ON <INPUT TYPE=\"Radio\" class = \"electric\" name=\"electric\" Value=\"6\" <?php echo (isset($id) && $id=='6')?'checked':'unchecked' ?> MOTOR OFF >";
//out <<"</div>";

//out <<"<script  src=\"jquery.js\"></script>";

//out << "<script>";
//out <<" $(\".electric\").click(function() {  var id = $(this).val();  alert(id); if(id >4){ var content=id; var id = '<?php echo $id; ?>'; if(id){ id = id; } else{ id=''; }} window.location.href = \"getvalue.php?id=\"+id;}); ";

//out<<" </script>";

out <<"<body bgcolor=\"08F35A\">";
//out<<"<html>";
out << " <form  name=\"input1\" action=\"new1.php\" method=\"post\">";
out<<"set value: <textarea  name=\"prio1\"></textarea>";
out<<"<input type=\"submit\" value=\"Submit\">";
out<<"</form>";
out<<" </body</html>" ;

out <<"<body bgcolor=\"08F35A\">";
out <<"</body";
out<<"</html>";

file1.close();
QDir dir;
dir.remove("/var/www/html/index.html");
dir.rename("/var/www/html/index.txt","/var/www/html/index.html");


//system("rm /var/www/html/data.txt");

    }



void MainWindow::on_pushButton_clicked()
{

  int val;

   ret= fopen("data1.txt", "r");



    if(ret)
    {
        fscanf(ret,"%d",&val);
        qDebug()<<val;
    }
   // close(set);


    write(fd,enroll,12);
    sleep(1);
     read(fd,readtemp,16);
     sleep(1);
      write(fd,generate_ch,13);
       sleep(1);
        read(fd,readtemp,16);
        sleep(1);
        write(fd,identify,17);
       sleep(1);
          read(fd,readtemp,16);
        sleep(1);
qDebug()<<"enroll 1"<<readtemp[0];
qDebug()<<"enroll 2"<<readtemp[1];
qDebug()<<"enroll 3"<<readtemp[2];
qDebug()<<"enroll 4"<<readtemp[3];
qDebug()<<"enroll 5"<<readtemp[4];
qDebug()<<"enroll 6"<<readtemp[5];
qDebug()<<"enroll 7"<<readtemp[6];
qDebug()<<"enroll 8"<<readtemp[7];
qDebug()<<"enroll 9"<<readtemp[8];
qDebug()<<"enroll 10"<<readtemp[9];
qDebug()<<"enroll 11"<<readtemp[10];
qDebug()<<"enroll 12"<<readtemp[11];
qDebug()<<"enroll 13"<<readtemp[12];
qDebug()<<"enroll 14"<<readtemp[13];
qDebug()<<"enroll 15"<<readtemp[14];
qDebug()<<"enroll 16\n"<<readtemp[15];


if(readtemp[9] == 0)
{
if(readtemp[11] == 2 && val == 2)
{


    if(num1)
    {
    ui->status_2->setText(QString::number(list[0])+" logout  sucess");
    qDebug()<<"finger 1";
    num1 = false;
   QDateTime dateTime = QDateTime::currentDateTime();
   QString dateTimeString = dateTime.toString();
   ui->date->setText("Date and Time: " + dateTimeString);
   out1 << "log out1 at  "  << dateTimeString << " id " << list[0] << "\n";

    }
    else
        ui->status_2->setText("No login Details found");


}
else if(readtemp[11]==3 && val == 3)
{


    if(num2)
    {
    ui->status_2->setText(QString::number(list[1])+" logout  sucess");
    qDebug()<<"finger 2";
    num2 = false;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString();
    ui->date->setText(dateTimeString);
    out1 << "log out1 at  " << dateTimeString << " id " << list[1]<< "\n";

    }
    else
        ui->status_2->setText("No login Details found");

}
else if(readtemp[11] == 4 && val == 4)
{


    if(num3)
    {
    ui->status_2->setText(QString::number(list[2])+" logout  sucess");
    qDebug()<<"finger 1";
    num3= false;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString();
    ui->date->setText(dateTimeString);

    out1 << "log out1 at  " << dateTimeString << " id " << list[2]<< "\n";

    }
    else
        ui->status_2->setText("No login Details found");

}
else if(readtemp[11] == 5 && val == 5)
{


    if(num4)
    {
    ui->status_2->setText(QString::number(list[3])+" logout  sucess");
    qDebug()<<"finger 3";
    num4 = false;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString();
    ui->date->setText(dateTimeString);
    out1 << "log out1 at  " << dateTimeString << " id " << list[3]<< "\n";

    }
    else
        ui->status_2->setText("No login Details found");

}
else if(readtemp[11] == 6 && val == 6)
{

    if(num5)
    {
    ui->status_2->setText(QString::number(list[4])+" logout  sucess");
    qDebug()<<"finger 4";
    num5 = false;
    QDateTime dateTime = QDateTime::currentDateTime();
    QString dateTimeString = dateTime.toString();
    ui->date->setText(dateTimeString);
    out1 << "log out1 at  " << dateTimeString << " id " << list[4]<< "\n";

    }
    else
        ui->status_2->setText("No login Details found");

}

}
else
    ui->status_2->setText("Take permission from HOD and \n try agin");




}
