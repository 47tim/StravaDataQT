#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QMessageBox>
#include <QList>
#include <QString>
#include <QFile>
#include <QProcess>

// TO-DO (8/20/2021)
// Add fail safe so you can't go into negative number activites when on individual day mode
// Add the start time to the date when on the individual day mode
// Make graph information easier to understand to other people. Axis.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeData(){

       ui->timeLabel->setText("  All Time   ");
       readStrings();
       numActivities = distance.size();
       readVectors();

       setTimePeriod_ALLTIME();
       setStats();
       setGraphs();
       setDates();
       checker++;

       ui->lineEdit->setValidator( new QDoubleValidator(0, 100, 3, this) ); // for the input line

}


void MainWindow::setDates(){

    QString startYear, endYear, startDay, endDay, startMonth, endMonth;

    QString finalStart, finalEnd, finalTogether;

    for (int i = 0; i < 4; i++){
        startYear.append(START_DATE_LOCAL[0].at(i));
        endYear.append(START_DATE_LOCAL[START_DATE_LOCAL.size() - 1].at(i));
    }

    for (int i = 5; i < 7; i++){
        startMonth.append(START_DATE_LOCAL[0].at(i));
        endMonth.append(START_DATE_LOCAL[START_DATE_LOCAL.size() - 1].at(i));
    }

    for (int i = 8; i < 10; i++){
        startDay.append(START_DATE_LOCAL[0].at(i));
        endDay.append(START_DATE_LOCAL[START_DATE_LOCAL.size() - 1].at(i));
    }

    finalStart.append(startMonth + "/" + startDay + "/" + startYear);
    finalEnd.append(endMonth + "/" + endDay + "/" + endYear);
    finalTogether.append(finalStart + " - " + finalEnd);

    ui->label_dates->setText(finalTogether);

}

void MainWindow::deleteData(){
    DISTANCE.clear();
    MAX_HEARTRATE.clear();
    AVERAGE_HEARTRATE.clear();
    MOVING_TIME.clear();
    START_DATE_LOCAL.clear();
    TOTAL_ELEVATION_GAIN.clear();
}

void MainWindow::setTimePeriod_ALLTIME(){

    timePeriod = 0; // used for replotting graphs
    currentGraphs = 0;

    DISTANCE.clear();
    MAX_HEARTRATE.clear();
    AVERAGE_HEARTRATE.clear();
    MOVING_TIME.clear();
    START_DATE_LOCAL.clear();
    TOTAL_ELEVATION_GAIN.clear();

    for (int i = 0; i < distance.size(); i++){
        DISTANCE.push_back(distance[i]);
        MAX_HEARTRATE.push_back(max_heartrate[i]);
        AVERAGE_HEARTRATE.push_back(average_heartrate[i]);
        MOVING_TIME.push_back(moving_time[i]);
        START_DATE_LOCAL.push_back(start_date_local[i]);
        TOTAL_ELEVATION_GAIN.push_back(total_elevation_gain[i]);
    }
}

void MainWindow::setTimePeriod_50(){

    timePeriod = 1;
    currentGraphs = 1;

    DISTANCE.clear();
    MAX_HEARTRATE.clear();
    AVERAGE_HEARTRATE.clear();
    MOVING_TIME.clear();
    START_DATE_LOCAL.clear();
    TOTAL_ELEVATION_GAIN.clear();

    for (int i = 0; i < distance_50.size(); i++){
        DISTANCE.push_back(distance_50[i]);
        MAX_HEARTRATE.push_back(max_heartrate_50[i]);
        AVERAGE_HEARTRATE.push_back(average_heartrate_50[i]);
        MOVING_TIME.push_back(moving_time_50[i]);
        START_DATE_LOCAL.push_back(start_date_local_50[i]);
        TOTAL_ELEVATION_GAIN.push_back(total_elevation_gain_50[i]);
    }
}

void MainWindow::setTimePeriod_10(){

    timePeriod = 1;
    currentGraphs = 2;

    DISTANCE.clear();
    MAX_HEARTRATE.clear();
    AVERAGE_HEARTRATE.clear();
    MOVING_TIME.clear();
    START_DATE_LOCAL.clear();
    TOTAL_ELEVATION_GAIN.clear();

    for (int i = 0; i < distance_10.size(); i++){
        DISTANCE.push_back(distance_10[i]);
        MAX_HEARTRATE.push_back(max_heartrate_10[i]);
        AVERAGE_HEARTRATE.push_back(average_heartrate_10[i]);
        MOVING_TIME.push_back(moving_time_10[i]);
        START_DATE_LOCAL.push_back(start_date_local_10[i]);
        TOTAL_ELEVATION_GAIN.push_back(total_elevation_gain_10[i]);
    }
}

void MainWindow::setTimePeriod_5(){

    timePeriod = 1;
    currentGraphs = 3;

    DISTANCE.clear();
    MAX_HEARTRATE.clear();
    AVERAGE_HEARTRATE.clear();
    MOVING_TIME.clear();
    START_DATE_LOCAL.clear();
    TOTAL_ELEVATION_GAIN.clear();

    for (int i = 0; i < distance_5.size(); i++){
        DISTANCE.push_back(distance_5[i]);
        MAX_HEARTRATE.push_back(max_heartrate_5[i]);
        AVERAGE_HEARTRATE.push_back(average_heartrate_5[i]);
        MOVING_TIME.push_back(moving_time_5[i]);
        START_DATE_LOCAL.push_back(start_date_local_5[i]);
        TOTAL_ELEVATION_GAIN.push_back(total_elevation_gain_5[i]);
    }
}

void MainWindow::readStrings(){


    // READING IN FILES TO THE ALL TIME VECTORS ******************************************************

    QString path1 = path;       // uses the user path defined in the header file
    path1.append("name.txt");   // I didn't include the .txt files as a qrc file
                                // because I want them to still be editable by python script
    QFile file(path1);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "failed to open0";
        return;
     }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        name.push_back(line);
    }

    file.close();
    //==================================================================================

    QString path2 = path;
    path2.append("distance.txt");

    QFile file1(path2);

    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "failed to open1";
        return;
     }

    QTextStream in1(&file1);
    while (!in1.atEnd()) {
        QString line1 = in1.readLine();
        distance.push_back(line1.toDouble());
    }

    file1.close();
    //==================================================================================

    QString path3 = path;
    path3.append("max_heartrate.txt");

    QFile file2(path3);

    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "failed to open2";
        return;
     }

    QTextStream in2(&file2);
    while (!in2.atEnd()) {
        QString line2 = in2.readLine();
        max_heartrate.push_back(line2.toDouble());
    }

    file2.close();
    //==================================================================================

    QString path4 = path;
    path4.append("average_heartrate.txt");

    QFile file3(path4);

    if (!file3.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "failed to open3";
        return;
     }

    QTextStream in3(&file3);
    while (!in3.atEnd()) {
        QString line3 = in3.readLine();
        average_heartrate.push_back(line3.toDouble());
    }

    file3.close();
    //==================================================================================

    QString path5 = path;
    path5.append("moving_time.txt");

    QFile file4(path5);

    if (!file4.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "failed to open4";
        return;
     }

    QTextStream in4(&file4);
    while (!in4.atEnd()) {
        QString line4 = in4.readLine();
        moving_time.push_back(line4.toDouble());
    }

    file4.close();
    //==================================================================================

    QString path6 = path;
    path6.append("start_date_local.txt");

    QFile file5(path6);

    if (!file5.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "failed to open5";
        return;
     }

    QTextStream in5(&file5);
    while (!in5.atEnd()) {
        QString line5 = in5.readLine();
        start_date_local.push_back(line5);
    }

    file5.close();
    //==================================================================================

    QString path7 = path;
    path7.append("total_elevation_gain.txt");

    QFile file6(path7);

    if (!file6.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "failed to open6";
        return;
     }

    QTextStream in6(&file6);
    while (!in6.atEnd()) {
        QString line6 = in6.readLine();
        total_elevation_gain.push_back(line6.toDouble());
    }

    file6.close();

}

void MainWindow::readVectors(){

    //-------------- SETTING VECTORS OF LAST 50 ACTIVITIES--------------------

    for (int i = 0; i < numActivities; i++){
        distance_50.push_back(distance[i]);
    }
    for (int i = 0; i < numActivities - 50; i++){
      distance_50.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        max_heartrate_50.push_back(max_heartrate[i]);
    }
    for (int i = 0; i < numActivities - 50; i++){
      max_heartrate_50.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        average_heartrate_50.push_back(average_heartrate[i]);
    }
    for (int i = 0; i < numActivities - 50; i++){
      average_heartrate_50.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        moving_time_50.push_back(moving_time[i]);
    }
    for (int i = 0; i < numActivities - 50; i++){
      moving_time_50.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        start_date_local_50.push_back(start_date_local[i]);
    }
    for (int i = 0; i < numActivities - 50; i++){
      start_date_local_50.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        total_elevation_gain_50.push_back(total_elevation_gain[i]);
    }
    for (int i = 0; i < numActivities - 50; i++){
      total_elevation_gain_50.removeFirst();
    }

    //-------------- SETTING VECTORS OF LAST 10 ACTIVITIES--------------------

    for (int i = 0; i < numActivities; i++){
        distance_10.push_back(distance[i]);
    }
    for (int i = 0; i < numActivities - 10; i++){
      distance_10.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        max_heartrate_10.push_back(max_heartrate[i]);
    }
    for (int i = 0; i < numActivities - 10; i++){
      max_heartrate_10.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        average_heartrate_10.push_back(average_heartrate[i]);
    }
    for (int i = 0; i < numActivities - 10; i++){
      average_heartrate_10.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        moving_time_10.push_back(moving_time[i]);
    }
    for (int i = 0; i < numActivities - 10; i++){
      moving_time_10.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        start_date_local_10.push_back(start_date_local[i]);
    }
    for (int i = 0; i < numActivities - 10; i++){
      start_date_local_10.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        total_elevation_gain_10.push_back(total_elevation_gain[i]);
    }
    for (int i = 0; i < numActivities - 10; i++){
      total_elevation_gain_10.removeFirst();
    }

     //-------------- SETTING VECTORS OF LAST 5 ACTIVITIES--------------------

    for (int i = 0; i < numActivities; i++){
        distance_5.push_back(distance[i]);
    }
    for (int i = 0; i < numActivities - 5; i++){
      distance_5.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        max_heartrate_5.push_back(max_heartrate[i]);
    }
    for (int i = 0; i < numActivities - 5; i++){
      max_heartrate_5.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        average_heartrate_5.push_back(average_heartrate[i]);
    }
    for (int i = 0; i < numActivities - 5; i++){
      average_heartrate_5.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        moving_time_5.push_back(moving_time[i]);
    }
    for (int i = 0; i < numActivities - 5; i++){
      moving_time_5.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        start_date_local_5.push_back(start_date_local[i]);
    }
    for (int i = 0; i < numActivities - 5; i++){
      start_date_local_5.removeFirst();
    }

    for (int i = 0; i < numActivities; i++){
        total_elevation_gain_5.push_back(total_elevation_gain[i]);
    }
    for (int i = 0; i < numActivities - 5; i++){
      total_elevation_gain_5.removeFirst();
    }

}

void MainWindow::setStats(){

    ui->label_d_2->setText(""); // setting the daily stats to show nothing
    ui->label_t_2->setText("");
    ui->label_p_2->setText("");
    ui->label10->setText("");
    ui->label12->setText("");
    ui->label_dates->setStyleSheet("color: rgb(146, 145, 147); font: 57 18pt 'Futura'");
    ui->lineEdit->setVisible(false);
    ui->toolButton_3->setVisible(false);
    ui->toolButton_2->setVisible(false);
    ui->toolButton->setVisible(false);

    double count = 0;
    for (int i = 0; i < DISTANCE.size(); i++){
        count += DISTANCE[i];
    }
    double average_distance = count / DISTANCE.size();
    QString valueAsString = QString::number(average_distance);
    ui->label1->setText(valueAsString);

    int count2 = 0;
    for (int i = 0; i < MAX_HEARTRATE.size(); i++){
        count2+= MAX_HEARTRATE[i];
    }
    int average_max_heartrate = count2 / MAX_HEARTRATE.size();
    QString valueAsString2 = QString::number(average_max_heartrate);
    ui->label2->setText(valueAsString2);

    int count3 = 0;
    for (int i = 0; i < AVERAGE_HEARTRATE.size(); i++){
        count3+= AVERAGE_HEARTRATE[i];
    }
    int average_average_heartrate = count3 / AVERAGE_HEARTRATE.size();
    QString valueAsString3 = QString::number(average_average_heartrate);
    ui->label3->setText(valueAsString3);

    double count4 = 0;
    for (int i = 0; i < MOVING_TIME.size(); i++){
        count4 += MOVING_TIME[i];
    }
    double pace = count4 / count;
    double integral;
    double fractional = modf(pace, &integral);
    int seconds = fractional * 60;
    QString valueAsString4 = QString::number(integral);
    valueAsString4.append(":");
    if (seconds < 10){                 // adding a 0 so the pace wont show up as ex. 21:6, for 21:06
        valueAsString4.append("0");
    }
    valueAsString4.append(QString::number(seconds));
    ui->label4->setText(valueAsString4);

    double avg_time = count4 / MOVING_TIME.size();
    double integral2;
    double fractional2 = modf(avg_time, &integral2);
    int seconds2 = fractional2 * 60;
    QString valueAsString5 = QString::number(integral2);
    valueAsString5.append(":");
    if (seconds2 < 10){
        valueAsString5.append("0");
    }
    valueAsString5.append(QString::number(seconds2));
    ui->label5->setText(valueAsString5);

    double count5 = 0;
    for (int i = 0; i < TOTAL_ELEVATION_GAIN.size(); i++){
        count5 += TOTAL_ELEVATION_GAIN[i];
    }
    int avg_elevation = count5 / TOTAL_ELEVATION_GAIN.size();
    QString valueAsString6 = QString::number(avg_elevation);
    valueAsString6.append(" ft");
    ui->label6->setText(valueAsString6);

}

void MainWindow::setGraphs(){

    ui->widget1->setVisible(true);
    ui->widget2->setVisible(true);
    ui->widget3->setVisible(true);

    plot1();
    plot2();
    plot3();

}

void MainWindow::plot1(){

    QVector<double> v_distance;   // plot only accepts vectors, so converting from list

    for (int i = 0; i < DISTANCE.size(); i++){
        v_distance.push_back(DISTANCE[i]);
    }

    QVector<double> y;

    int counter = 1;

    for (int i = 0; i < DISTANCE.size(); i++){
        y.push_back(counter);
        counter++;
    }

    QCPBars *newbars=new QCPBars(ui->widget1->xAxis , ui->widget1->yAxis);
    ui->widget1->plottable();
    newbars->setData(y ,v_distance);
    ui->widget1->xAxis->setRange(1, DISTANCE.size());
    ui->widget1->yAxis->setRange(0, 12);
    ui->widget1->replot();
    ui->widget1->setBackground(QColor(46, 49, 49, 255));
    newbars->setPen(QPen(Qt::cyan));
    newbars->setBrush(QColor(Qt::cyan));

    ui->widget1->xAxis->setTickLabelColor(Qt::white);
    ui->widget1->xAxis->setLabelColor(Qt::white);
    ui->widget1->xAxis->setTickPen(QPen(Qt::white));
    ui->widget1->xAxis->setSubTickPen(QPen(Qt::white));
    ui->widget1->yAxis->setTickLabelColor(Qt::white);
    ui->widget1->yAxis->setLabelColor(Qt::white);
    ui->widget1->yAxis->setTickPen(QPen(Qt::white));
    ui->widget1->yAxis->setSubTickPen(QPen(Qt::white));

    ui->widget1->xAxis->setLabel("Distance (mi)");

    ui->widget1->replot();

}

void MainWindow::plot2(){

    QVector<double> v_max_heartrate;   // plot only accepts vectors, so converting from list

    for (int i = 0; i < MAX_HEARTRATE.size(); i++){
        v_max_heartrate.push_back(MAX_HEARTRATE[i]);
    }

    QVector<double> y;

    int counter = 1;

    for (int i = 0; i < MAX_HEARTRATE.size(); i++){
        y.push_back(counter);
        counter++;
    }
    QCPBars *newbars2=new QCPBars(ui->widget2->xAxis , ui->widget2->yAxis);
    ui->widget2->plottable();
    newbars2->setData(y ,v_max_heartrate);
    ui->widget2->xAxis->setRange(1, MAX_HEARTRATE.size());
    ui->widget2->yAxis->setRange(150, 210);
    ui->widget2->replot();
    ui->widget2->setBackground(QColor(46, 49, 49, 255));
    newbars2->setPen(QPen(Qt::red));
    newbars2->setBrush(QColor(Qt::red));

    ui->widget2->xAxis->setTickLabelColor(Qt::white);
    ui->widget2->xAxis->setLabelColor(Qt::white);
    ui->widget2->xAxis->setTickPen(QPen(Qt::white));
    ui->widget2->xAxis->setSubTickPen(QPen(Qt::white));
    ui->widget2->yAxis->setTickLabelColor(Qt::white);
    ui->widget2->yAxis->setLabelColor(Qt::white);
    ui->widget2->yAxis->setTickPen(QPen(Qt::white));
    ui->widget2->yAxis->setSubTickPen(QPen(Qt::white));

    ui->widget2->xAxis->setLabel("Max Heartrate");

    ui->widget2->replot();

}

void MainWindow::plot3(){

    QVector<double> v_average_heartrate;

    for (int i = 0; i < AVERAGE_HEARTRATE.size(); i++){
        v_average_heartrate.push_back(AVERAGE_HEARTRATE[i]);
    }

    QVector<double> y;

    int counter = 1;

    for (int i = 0; i < MAX_HEARTRATE.size(); i++){
        y.push_back(counter);
        counter++;
    }

     QCPBars *newbars3=new QCPBars(ui->widget3->xAxis , ui->widget3->yAxis);
     ui->widget3->plottable();
     newbars3->setData(y ,v_average_heartrate);
     ui->widget3->xAxis->setRange(1, AVERAGE_HEARTRATE.size());
     ui->widget3->yAxis->setRange(150, 210);
     ui->widget3->replot();
     ui->widget3->setBackground(QColor(46, 49, 49, 255));
     newbars3->setPen(QPen(Qt::cyan));
     newbars3->setBrush(QColor(Qt::cyan));

     ui->widget3->xAxis->setTickLabelColor(Qt::white);
     ui->widget3->xAxis->setLabelColor(Qt::white);
     ui->widget3->xAxis->setTickPen(QPen(Qt::white));
     ui->widget3->xAxis->setSubTickPen(QPen(Qt::white));
     ui->widget3->yAxis->setTickLabelColor(Qt::white);
     ui->widget3->yAxis->setLabelColor(Qt::white);
     ui->widget3->yAxis->setTickPen(QPen(Qt::white));
     ui->widget3->yAxis->setSubTickPen(QPen(Qt::white));

     ui->widget3->xAxis->setLabel("Average Heartrate");

     ui->widget3->replot();

}

void MainWindow::setDay(){ // only used if the day mode is selected

    ui->label_d_2->setText("Rounded Distance (mi)");
    ui->label_p_2->setText("Rounded Pace (m/mi)");
    ui->label_t_2->setText("Input Distance");

    int lastNum0 = start_date_local.size() - 1;
    ui->label_dates->setText(start_date_local[lastNum0 - day]);

    QString label2text;
    int lastNum = max_heartrate.size() - 1;
    label2text.push_back(QString::number(max_heartrate[lastNum - day]));
    ui->label2->setText(label2text);

    QString label3text;
    int lastNum2 = max_heartrate.size() - 1;
    label3text.push_back(QString::number(average_heartrate[lastNum2 - day]));
    ui->label3->setText(label3text);

    QString label6text;
    int lastNum3 = total_elevation_gain.size() - 1;
    label6text.push_back(QString::number(total_elevation_gain[lastNum3 - day]));
    ui->label6->setText(label6text);

    QString label1text;
    int lastNum4 = distance.size() - 1;
    label1text.push_back(QString::number(distance[lastNum4 - day]));
    ui->label1->setText(label1text);

    int lastNum5 = moving_time.size() - 1;
    double integral2;
    double fractional2 = modf(moving_time[lastNum5 - day], &integral2);
    int seconds2 = fractional2 * 60;
    QString valueAsString5 = QString::number(integral2);
    valueAsString5.append(":");
    if (seconds2 < 10){
        valueAsString5.append("0");
    }
    valueAsString5.append(QString::number(seconds2));
    ui->label5->setText(valueAsString5);

    double pace = (moving_time[lastNum5 - day]) / (distance[lastNum4 - day]);
    double integral;
    double fractional = modf(pace, &integral);
    int seconds = fractional * 60;
    QString valueAsString4 = QString::number(integral);
    valueAsString4.append(":");
    if (seconds < 10){
        valueAsString4.append("0");
    }
    valueAsString4.append(QString::number(seconds));
    ui->label4->setText(valueAsString4);

    QString label10text;
    double beforeRound = distance[lastNum4 - day];
    int rounded = round(beforeRound);
    label10text.append(QString::number(rounded));
    label10text.append(".00");
    ui->label10->setText(label10text);

    double roundedPace = (moving_time[lastNum5 - day]) / rounded;
    double integral3;
    double fractional3 = modf(roundedPace, &integral3);
    int seconds3 = fractional3 * 60;
    QString valueAsString6 = QString::number(integral3);
    valueAsString6.append(":");
    if (seconds3 < 10){
        valueAsString6.append("0");
    }
    valueAsString6.append(QString::number(seconds3));
    ui->label12->setText(valueAsString6);

    // SETTING TIME LABEL

    int lastNum8 = start_date_local.size() - 1;

    QString startYear, startDay, startMonth, finalStart;

    for (int i = 0; i < 4; i++){
        startYear.append(start_date_local[lastNum8 - day].at(i));
    }
    for (int i = 5; i < 7; i++){
        startMonth.append(start_date_local[lastNum8 - day].at(i));
    }
    for (int i = 8; i < 10; i++){
        startDay.append(start_date_local[lastNum8 - day].at(i));
    }
    finalStart.append(startMonth + "/" + startDay + "/" + startYear);

    ui->label_dates->setStyleSheet("color: rgb(161, 225, 255); font: 57 18pt 'Futura'");
    ui->label_dates->setText(finalStart);

}

void MainWindow::dayGraphs(){

   ui->widget1->setVisible(false);
   ui->widget2->setVisible(false);
   ui->widget3->setVisible(false);
}

//***********************-----------SLOTS----------****************************

void MainWindow::on_toolButton_7_clicked()
{
    onDayMode = false;
    if (currentGraphs != 3){
        ui->timeLabel->setText(" 5 Activities");
        ui->widget1->clearPlottables();
        ui->widget2->clearPlottables();
        setTimePeriod_5();
        setStats();
        setGraphs();
        setDates();
        deleteData();
    }
}


void MainWindow::on_toolButton_8_clicked()
{
    onDayMode = false;
    if (currentGraphs != 2){
        ui->timeLabel->setText("10 Activities");
        ui->widget1->clearPlottables();
        ui->widget2->clearPlottables();
        ui->widget3->clearPlottables();
        setTimePeriod_10();
        setStats();
        setGraphs();
        setDates();
        deleteData();
    }
}

void MainWindow::on_toolButton_9_clicked()
{
    onDayMode = false;
    if (currentGraphs != 1){
        ui->timeLabel->setText("50 Activities");
        ui->widget1->clearPlottables();
        ui->widget2->clearPlottables();
        setTimePeriod_50();
        setStats();
        setGraphs();
        setDates();
        deleteData();
    }
}

void MainWindow::on_toolButton_10_clicked()
{
    onDayMode = false;
    if (currentGraphs != 0){                    // checking to not double write
        ui->timeLabel->setText("  All Time   ");
        ui->widget1->clearPlottables();
        ui->widget2->clearPlottables();
        ui->widget3->clearPlottables();
        setTimePeriod_ALLTIME();
        setStats();
        setGraphs();
        setDates();
        deleteData();
    }
}

void MainWindow::on_toolButton_11_clicked()
{
    currentGraphs = -1;
    onDayMode = true;
    setDay();
    dayGraphs();
    ui->timeLabel->setText("     Day     ");
    ui->lineEdit->setVisible(true);
    ui->toolButton_3->setVisible(true);
    ui->toolButton_2->setVisible(true);
    ui->toolButton->setVisible(true);
}

void MainWindow::on_toolButton_clicked()
{

    if (onDayMode == true){
        currentGraphs = -1;
        day++;
        setDay();
        dayGraphs();
    }
}

void MainWindow::on_toolButton_2_clicked()
{
    if (onDayMode == true){
        if (day <= 0){
        }
        else {
            currentGraphs = -1;
            day--;
            setDay();
            dayGraphs();
        }
    }
}

void MainWindow::on_toolButton_3_clicked() // line edit button
{
    if (onDayMode == true){
        QString num = ui->lineEdit->text();
        double numDouble = num.toDouble();

        ui->label10->setText(QString::number(numDouble));

        int lastNum = distance.size() - 1;
        double pace = (moving_time[lastNum - day]) / numDouble;
        double integral3;
        double fractional3 = modf(pace, &integral3);
        int seconds3 = fractional3 * 60;
        QString valueAsString6 = QString::number(integral3);
        valueAsString6.append(":");
        if (seconds3 < 10){
            valueAsString6.append("0");
        }
        valueAsString6.append(QString::number(seconds3));
        ui->label12->setText(valueAsString6);
    }
}

