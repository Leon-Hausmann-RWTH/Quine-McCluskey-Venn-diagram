#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <QPainter>
#include <QPoint>
#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsView>
#include <QGraphicsScene>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct GroupElement
{
    vector<int> minterms; //Zahl des Mintterms
    vector<int> value; //Einsen und Nullen stehen für Buchstaben an der jeweiligen Stelle
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


    //Quine McCluskey
    pair<vector<int>, int> getMintermAndCount(const int minTerm, const int literalCount);
    map<int, vector<GroupElement>> mergeGroupElement(map<int, vector<GroupElement>> numberedGroups, int literals, vector<GroupElement> &notUpdated);
    void displayFormatedAnswer(set<vector<int>> answer);

    // All Print Functions
    void printMinterm(const vector<int> v);
    void printState(const vector<int> v);
    void printMintermWithDontCare(const vector<int> v, const set<int> dontCareSet);
    void printGroups(const map<int, vector<GroupElement>> allGroups, const set<int>dontCareSet);
    void printNotUpdated(vector<GroupElement> notUpdated);
    int get_number_from_string(string term, int literal_count);

    pair<vector<int>, int> scanner(string input);

    void init_q();

    //Drawings
    void setup();
    void draw_term(int term, QColor color);
    void draw_skeleton();
    void draw_solution(vector<int> solution);
    void draw_all_terms();

    void clear_scene();

private slots:
    void on_pushButton_minimiere_funktion_clicked();

    void on_pushButton_zeige_minimierte_darstellung_clicked();

    void on_pushButton_clear_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene scene;
    QPen pen;
    QPainterPath ellipse_a,ellipse_b,ellipse_c,ellipse_d, rect;
    QPainterPath _a_b_c_d;
    QPainterPath _a_b_cd;
    QPainterPath _a_bc_d;
    QPainterPath _a_bcd;
    QPainterPath _ab_c_d;
    QPainterPath _ab_cd;
    QPainterPath _abc_d;
    QPainterPath _abcd;
    QPainterPath a_b_c_d;
    QPainterPath a_b_cd;
    QPainterPath a_bc_d;
    QPainterPath a_bcd;
    QPainterPath ab_c_d;
    QPainterPath ab_cd;
    QPainterPath abc_d;
    QPainterPath abcd;

    QColor term_color;
    QColor min_term_color;
    QColor dont_care_color;

    set<vector<int>> global_answer;
    vector<int> global_answer_terms;
};
#endif // MAINWINDOW_H
