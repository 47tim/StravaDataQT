#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QString>
#include <QFile>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //=============================================================

    const int NUM_OF_CATEGORIES = 5;

    int timePeriod = 0;
    int currentGraphs;
    int checker = 0;
    int day = 0;
    bool onDayMode = false;

    void initializeData();
    void readStrings();
    void printStrings();
    void setStats();
    void readVectors();
    void setGraphs();
    void clearTables();
    void deleteData();
    void setDates();
    void setDay();

    void setTimePeriod_ALLTIME();
    void setTimePeriod_50();
    void setTimePeriod_10();
    void setTimePeriod_5();

    void plot1();
    void plot2();
    void plot3();

    void dayGraphs();



private slots:


    void on_toolButton_7_clicked();

    void on_toolButton_8_clicked();

    void on_toolButton_9_clicked();

    void on_toolButton_10_clicked();

    void on_toolButton_11_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

    void on_toolButton_3_clicked();

private:

    Ui::MainWindow *ui;

    QString path = "/Users/timhyde/Desktop/stravaDataFiles/"; // PUT YOUR FILE PATH HERE

    //==============================================================

    // IN THE INITIALIZE DATA FNCT:
    // --instantiate all vectors. 5, 10, 50, all time activities
    // --set the values of the CAPS vectors/variables to the current selected option.
    // ----(default is all time)
    // --go back in and replace all references to the stats to CAPS vectors/variables.

    //==============================================================


    QList<QString> name;             // these will be called by the functions which
    QList<double> DISTANCE;          // display data and graphs on screen
    QList<int> MAX_HEARTRATE;
    QList<int> AVERAGE_HEARTRATE;
    QList<double> MOVING_TIME;
    QList<QString> START_DATE_LOCAL;
    QList<double> TOTAL_ELEVATION_GAIN;

    // --------------------------------

    int numActivities;

    QList<double> distance;         // all time stats
    QList<int> max_heartrate;
    QList<int> average_heartrate;
    QList<double> moving_time;
    QList<QString> start_date_local;
    QList<double> total_elevation_gain;

    QList<double> distance_50;         // 50 activies
    QList<int> max_heartrate_50;
    QList<int> average_heartrate_50;
    QList<double> moving_time_50;
    QList<QString> start_date_local_50;
    QList<double> total_elevation_gain_50;

    QList<double> distance_10;         // 10 activies
    QList<int> max_heartrate_10;
    QList<int> average_heartrate_10;
    QList<double> moving_time_10;
    QList<QString> start_date_local_10;
    QList<double> total_elevation_gain_10;

    QList<double> distance_5;         // 5 activies
    QList<int> max_heartrate_5;
    QList<int> average_heartrate_5;
    QList<double> moving_time_5;
    QList<QString> start_date_local_5;
    QList<double> total_elevation_gain_5;



};
#endif // MAINWINDOW_H
