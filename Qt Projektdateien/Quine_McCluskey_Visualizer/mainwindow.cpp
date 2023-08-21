#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    setup();
    draw_skeleton();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw_all_terms(){
    // Header
    cout << "\nQuine McCluskey Minimization Technique\n";

    // SetUp
    cout << "\n--------------------------------------------------\n";


    int literalCount;
    cout << "Enter the number of Literals(greather than Zero): ";
    //cin >> literalCount;

    int minTermsCount;
    cout << "Number of Minterms: ";
    //cin >> minTermsCount;
    set<int> minTermsSet;
    cout << "Enter Minterms with space betweeen(eg. 1 2 3): " << endl;
    //for (int i = 0; i < minTermsCount; ++i)
    //{
    //    int minterm;
    //    cin >> minterm;
    //    minTermsSet.insert(minterm);
    //}

    int dontCareTermsCount;
    cout << "Number of DontCares: ";
    //cin >> dontCareTermsCount;
    set<int> dontCareTermsSet;
    cout << "Enter Dont Care Terms with space betweeen(eg. 1 2 3): " << endl;
    //for (int i = 0; i < dontCareTermsCount; ++i)
    //{
    //    int dontCareTerm;
    //    cin >> dontCareTerm;
    //    dontCareTermsSet.insert(dontCareTerm);
    //}

    cout << "\n--------------------------------------------------\n";

    /**
    literalCount=3;
    minTermsCount=2;
    dontCareTermsCount=2;

    minTermsSet.insert(4);
    minTermsSet.insert(5);

    dontCareTermsSet.insert(6);
    dontCareTermsSet.insert(7);
    */

    dontCareTermsCount=0;
    cout << "Hier alle Terme: " << endl;
    pair<vector<int>, int> result_terms = scanner(ui->lineEdit->text().toStdString());
    literalCount=result_terms.second;
    cout << "LiteralCount: " << literalCount << endl;
    for(auto i : result_terms.first){
        cout << i << endl;
        draw_term(i, QColor(255,100+rand()%150, 100+rand()%150, 230));
        minTermsSet.insert(i);
    }
    cout << "Ende" << endl;

    cout << "Hier alle Dont Cares: " << endl;
    pair<vector<int>, int> result_dont_cares = scanner(ui->lineEdit_2->text().toStdString());
    dontCareTermsCount = result_dont_cares.second;
    cout << "Dont Care Term count: " << dontCareTermsCount << endl;
    for(auto i : result_dont_cares.first){
        cout << i << endl;
        draw_term(i,dont_care_color);
        dontCareTermsSet.insert(i);
    }
    cout << "Ende" << endl;
}

void MainWindow::init_q(){
    // Header
    cout << "\nQuine McCluskey Minimization Technique\n";

    // SetUp
    cout << "\n--------------------------------------------------\n";


    int literalCount;
    cout << "Enter the number of Literals(greather than Zero): ";
    //cin >> literalCount;

    int minTermsCount;
    cout << "Number of Minterms: ";
    //cin >> minTermsCount;
    set<int> minTermsSet;
    cout << "Enter Minterms with space betweeen(eg. 1 2 3): " << endl;
    //for (int i = 0; i < minTermsCount; ++i)
    //{
    //    int minterm;
    //    cin >> minterm;
    //    minTermsSet.insert(minterm);
    //}

    int dontCareTermsCount;
    cout << "Number of DontCares: ";
    //cin >> dontCareTermsCount;
    set<int> dontCareTermsSet;
    cout << "Enter Dont Care Terms with space betweeen(eg. 1 2 3): " << endl;
    //for (int i = 0; i < dontCareTermsCount; ++i)
    //{
    //    int dontCareTerm;
    //    cin >> dontCareTerm;
    //    dontCareTermsSet.insert(dontCareTerm);
    //}

    cout << "\n--------------------------------------------------\n";

    /**
    literalCount=3;
    minTermsCount=2;
    dontCareTermsCount=2;

    minTermsSet.insert(4);
    minTermsSet.insert(5);

    dontCareTermsSet.insert(6);
    dontCareTermsSet.insert(7);
    */

    dontCareTermsCount=0;
    cout << "Hier alle Terme: " << endl;
    pair<vector<int>, int> result_terms = scanner(ui->lineEdit->text().toStdString());
    literalCount=result_terms.second;
    cout << "LiteralCount: " << literalCount << endl;
    for(auto i : result_terms.first){
        cout << i << endl;
        //draw_term(i, QColor(255,100+qrand()%150, 100+qrand()%150, 230));
        minTermsSet.insert(i);
    }
    cout << "Ende" << endl;

    cout << "Hier alle Dont Cares: " << endl;
    pair<vector<int>, int> result_dont_cares = scanner(ui->lineEdit_2->text().toStdString());
    dontCareTermsCount = result_dont_cares.second;
    cout << "Dont Care Term count: " << dontCareTermsCount << endl;
    for(auto i : result_dont_cares.first){
        cout << i << endl;
        //draw_term(i,dont_care_color);
        dontCareTermsSet.insert(i);
    }
    cout << "Ende" << endl;
    // Making Groups
    map<int, vector<GroupElement>> numberedGroups;

    // Adding minterms to the numberedGroups
    set<int> totalTerms;
    totalTerms.insert(minTermsSet.begin(), minTermsSet.end());
    totalTerms.insert(dontCareTermsSet.begin(), dontCareTermsSet.end());
    //Iteriere über alle Terme, Konvertiere Zahl in Binäre Darstellen, Speichere Informationen in Gruppenelement und Füge Gruppenelement in numberedGroups
    for (auto term : totalTerms)
    {
        pair<vector<int>, int> result = getMintermAndCount(term, literalCount);

        // Creating a group element
        GroupElement groupEle;
        groupEle.minterms.push_back(term); //Füge Zahl ein
        groupEle.value = result.first; //Füge einsen und Nullen ein

        // Adding group element to the respective group
        numberedGroups[result.second].push_back(groupEle); //Füge Mintterm (Gruppenelement in jeweilige Klasse ein)

        // Printing the minterm with its value
        cout << term << ": ";
        printMinterm(result.first);
        cout << "Einsen: " << result.second << endl;
        cout << endl;
    }

    // Now Printing the All the Groups
    cout << "\n--------------------------------------------------\n";
    cout << "Grouped Minterms And DontCares: \n" << endl;
    printGroups(numberedGroups, dontCareTermsSet);

    // Merging the Groups and printing them
    // and not updated groups are those which were not considred during merge
    vector<GroupElement> notUpdated;
    while (true) {
        map<int, vector<GroupElement>> newNumberedGroups = mergeGroupElement(numberedGroups, literalCount, notUpdated);

        if (newNumberedGroups.size() == 0 ) break;
        numberedGroups = newNumberedGroups;

        // Now Printing the All the Groups
        cout << "\n--------------------------------------------------\n";
        cout << "Grouped Minterms And DontCares: \n" << endl;
        printGroups(numberedGroups, dontCareTermsSet);
    }

    // Printing the terms which were left out
    cout << "\n--------------------------------------------------\n";
    cout << "Terms which were left when merging the groups" << endl;
    printNotUpdated(notUpdated);

    // Step to get the minterm and the table of them

    // going through the table and taking the minterms which appear only once in the table
    // and adding it to the answer
    //Speichert wie oft Welcher Mintterm abgedeckt ist
    map<int, int> countInTable;
    set<vector<int>> seenMinterms; // Used for identifying the seen minterms

    for (auto& group : numberedGroups) {
        for (auto& groupElement : group.second) {

            // Checking if the minterm is seen or not
            if (seenMinterms.count(groupElement.value)) continue;
            seenMinterms.insert(groupElement.value);

            // Adding minterms to the table
            for (auto& minterm : groupElement.minterms) {
                if (!dontCareTermsSet.count(minterm)) {
                    countInTable[minterm]++;
                }
            }
        }
    }

    // Adding other prime implicants which were lost during merging
    for (auto& groupElement : notUpdated) {
        if (seenMinterms.count(groupElement.value)) continue;
        seenMinterms.insert(groupElement.value);
        // printState(groupElement.value);
        // cout << endl;
        for (auto& minterm : groupElement.minterms) {
            if (!dontCareTermsSet.count(minterm)) {
                countInTable[minterm]++;
            }
        }
    }

    // Now we will extract the answer
    set<vector<int>> answer;
    vector<int> answer_terms;

    // it stroes the individual terms used so that we can check which terms are remaining
    set<int> termsTaken;
    for (auto& cell : countInTable) {
        if (cell.second == 1)
        {
            for (auto& gp : numberedGroups) {
                for (auto& ele : gp.second) {
                    int count = 0;
                    for (auto& num : ele.minterms) {
                        if (cell.first == num)count++;
                    }
                    if (count != 0) {
                        answer.insert(ele.value);
                        answer_terms.insert(answer_terms.end(), ele.minterms.begin(), ele.minterms.end());
                        QColor temp_color = QColor(rand()%180,150+rand()%100,rand()%180);
                        for (auto& num : ele.minterms) {

                            draw_term(num, temp_color);
                            termsTaken.insert(num);
                        }
                    }
                }
            }

            if (!termsTaken.count(cell.first)){
                for (auto& gp : notUpdated) {
                    int count = 0;
                    for (auto& num : gp.minterms) {
                        if (cell.first == num)count++;
                    }
                    if (count != 0) {
                        answer.insert(gp.value);
                        answer_terms.insert(answer_terms.end(), gp.minterms.begin(), gp.minterms.end());
                        QColor temp_color1 = QColor(rand()%180,150+rand()%100,rand()%180);
                        for (auto& num : gp.minterms) {

                            draw_term(num, temp_color1);
                            termsTaken.insert(num);
                        }
                    }
                }
            }

        }
    }

    // Printing the table
    cout << "\n--------------------------------------------------\n";
    cout << "Terms with the occurnce of them: " << endl;
    for (auto& i : countInTable) {
        cout << i.first << ": " << i.second << endl;
    }

    // Finding the elements left in countable which are not included
    // The logic suggest that if the term is in the count table then it is in any of the elements

    for (auto& iterator : countInTable) {
        if (!termsTaken.count(iterator.first))
        {
            bool flag = false;
            // cout << iterator.first << endl;
            for (auto& gp : numberedGroups) {
                for (auto& ele : gp.second) {
                    QColor temp_color2 = QColor(rand()%180,150+rand()%100,rand()%180);
                    for (auto& j : ele.minterms) {
                        if (iterator.first == j) {
                            answer.insert(ele.value);
                            answer_terms.insert(answer_terms.end(), ele.minterms.begin(), ele.minterms.end());

                            draw_term(j, temp_color2);
                            flag = true;
                            break;
                        }
                    }
                    if (flag) break;
                }
                if (flag) break;
            }

            // Checking if it is present
            for (auto& j : notUpdated) {
                QColor temp_color3 = QColor(rand()%180,150+rand()%100,rand()%180);
                for (auto& k : j.minterms) {
                    if (iterator.first == k) {
                        answer.insert(j.value);
                        answer_terms.insert(answer_terms.end(), j.minterms.begin(), j.minterms.end());

                        draw_term(k, temp_color3);
                        flag = true;
                        break;
                    }
                }
                if (flag) break;
            }
        }
    }

    // This is for the remaining onesfor which is not included
    QColor temp_color4 = QColor(rand()%180,150+rand()%100,rand()%180);
    for (auto& minterm : minTermsSet) {
        if (!countInTable.count(minterm)) {
            answer.insert(getMintermAndCount(minterm, literalCount).first);
            answer_terms.push_back(minterm);

            draw_term(minterm, temp_color4);
        }
    }

    cout << "Hallo" << endl;

    // showing the answer
    cout << "\n--------------------------------------------------\n";
    cout << "The Minimized Equation is: ";
    global_answer=answer;
    global_answer_terms=answer_terms;
    displayFormatedAnswer(answer);
    //draw_solution(answer_terms);
}

//Berechnet aus der Zahl den Minterm und fügt die Anzahl an einsen hinzu
pair<vector<int>, int> MainWindow::getMintermAndCount(const int minTerm, const int literalCount) {
    vector<int> mintermVector;
    int onesCount = 0;

    for (int i = 0; i < literalCount; ++i)
    {
        if (minTerm & 1 << (literalCount - i - 1)) {
            mintermVector.push_back(1);
            onesCount++;
        }
        else
        {
            mintermVector.push_back(0);
        }
    }

    pair<vector<int>, int> mintermAndCount;
    mintermAndCount.first = mintermVector;
    mintermAndCount.second = onesCount;

    return mintermAndCount;
}

// merging function
//Geht durch alle Gruppen, Dann durch alle Gruppen Elemente, Dann durch alle Gruppen Elemente der Klasse darunter, dann durch alle Variablen,
//Falls Differenz==1 erhöhe updatecount,whileGroupNotUpdated, Erstellt neues Gruppenelement, Setze zu vernachlässigende Variable auf -1
// Füge eigenen Mintterm hinzu, Füge alle Minterme des nextGroupElement hinzu, Füge NewGroupElement zu newNumberedGroups hinzu
map<int, vector<GroupElement>> MainWindow::mergeGroupElement(map<int, vector<GroupElement>> numberedGroups, int literals, vector<GroupElement> &notUpdated) {
    // Merged groups will be added here
    map<int, vector<GroupElement>> newNumberedGroups;
    int updateCount = 0;

    set<vector<int>> termsUsed;

    for (auto& group : numberedGroups) {
        if (numberedGroups.count(group.first + 1))
        {
            int wholeGroupNotUpdated = 0;
            for (auto& groupElement : group.second) {
                // Checking if next group is present or not
                // Comparing the elements with the next group elements
                for (auto& nextGroupElement : numberedGroups[group.first + 1]) {
                    int diffIndex = -1;
                    int diffCount = 0;

                    for (int i = 0; i < literals; ++i)
                    {
                        if (groupElement.value[i] != nextGroupElement.value[i]) {
                            diffIndex = i;
                            diffCount++;
                        }
                    }

                    if (diffCount == 1) {
                        updateCount++;
                        wholeGroupNotUpdated++;

                        GroupElement newGroupElement;

                        newGroupElement.value = groupElement.value;
                        newGroupElement.value[diffIndex] = -1;

                        // Adding new minters

                        newGroupElement.minterms = groupElement.minterms;
                        for (auto& m : nextGroupElement.minterms) {
                            newGroupElement.minterms.push_back(m);
                        }

                        termsUsed.insert(groupElement.minterms);
                        termsUsed.insert(nextGroupElement.minterms);

                        // Adding new numbered group
                        newNumberedGroups[group.first].push_back(newGroupElement);
                    }
                }
            }
        }
    }

    if (updateCount == 0) return {};

    for (auto& group : numberedGroups) {
        for (auto& groupElement : group.second) {
            if (!termsUsed.count(groupElement.minterms))
            {
                notUpdated.push_back(groupElement);
            }
        }
    }

    return newNumberedGroups;
}

void MainWindow::displayFormatedAnswer(set<vector<int>> answer) {
    int count=0;
    QString solution = "Lösung: ";
    for (auto& i : answer) {
        char letter = 'A';
        //cout << "In Außerer Schleife";
        for (auto& j : i) {
            //cout << "In Innerer Schleife: " << j;
            if (j != -1) {
                if (j == 1)
                {
                    cout << letter;
                    solution.append(letter);
                } else {
                    cout << "~" << letter;
                    solution.append("~");
                    solution.append(letter);
                }
            }
            letter++;
        }
        count++;
        if(count!=answer.size()){
            cout << " + ";
            solution.append("+");
        }

    }
    cout << endl;
    ui->label_loesung->setText(solution);
    //cout << "\b\b" << "  " << endl;

}

void MainWindow::printMinterm(const vector<int> v) {
    for (int i = 0; i < v.size(); ++i)	{
        cout << v[i] << " ";
    }
}

void MainWindow::printState(const vector<int> v) {
    for (int i = 0; i < v.size(); ++i)	{
        if (v[i] == -1)
        {
            cout << "_" << " ";
        } else {
            cout << v[i] << " ";
        }
    }
}

void MainWindow::printMintermWithDontCare(const vector<int> v, const set<int> dontCareSet) {
    for (int i = 0; i < v.size(); ++i)	{
        if (dontCareSet.count(v[i])) cout << v[i] << "* ";
        else cout << v[i] << "  ";
    }
}

void MainWindow::printGroups(const map<int, vector<GroupElement>> allGroups, const set<int>dontCareSet) {
    for (auto& group : allGroups) {
        cout << "Group " << group.first << endl;
        for (auto& groupElement : group.second) {
            printMintermWithDontCare(groupElement.minterms, dontCareSet);
            cout << ": ";
            printState(groupElement.value);
            cout << endl;
        }
    }
}

void MainWindow::printNotUpdated(vector<GroupElement> notUpdated) {
    cout << endl;
    for (auto& groupElement : notUpdated) {
        printMinterm(groupElement.minterms);
        cout << ": ";
        printState(groupElement.value);
        cout << endl;
    }
    cout << endl;
}

void MainWindow::on_pushButton_minimiere_funktion_clicked()
{
    this->clear_scene();
    init_q();
}

int MainWindow::get_number_from_string(string term, int literal_count){

    int current_count=literal_count-1;
    int sum=0;
    for(int j=0; j<term.length(); j++){
        if(term.at(j)=='~'){
            j++;
            current_count--;
        }else{
            sum+=pow(2,current_count);
            current_count--;
        }
    }
    //cout << "Sum: " << sum << endl;
    return sum;
}


pair<vector<int>, int> MainWindow::scanner(string input){
    vector<int> result_vec;
    int literal_count=0;
    //cout << "Input: " << input << endl;
    int first_index=0;
    for(int i=0; i<input.length(); i++){
        if(input.at(i)=='+' || i==(input.length()-1)){
            string temp;
            if(input.at(i)=='+'){
                temp = input.substr(first_index,i);
            }else{
                temp = input.substr(first_index,i+1);
            }
            cout << "Temp: " << temp << endl;
            if(first_index==0){
                for(int j=0; j<temp.length(); j++){
                    if(temp.at(j)=='~'){
                        j++;
                        literal_count++;
                    }else{
                        literal_count++;
                    }
                }
            }
            cout << "Literal_count: " << literal_count << endl;
            result_vec.push_back(get_number_from_string(temp, literal_count));
            first_index=i+1;
        }
    }
    pair<vector<int>, int> result;
    result.first=result_vec;
    result.second=literal_count;
    return result;
}


//Drawings
void MainWindow::setup(){

    ellipse_a.addEllipse(24,76,190,400);
    ellipse_b.addEllipse(120,76,190,400);
    ellipse_c.addEllipse(50,150,400,190);
    ellipse_d.addEllipse(50,50,400,190);
    rect.addRect(0,0,500,500);

    _a_b_c_d = rect-ellipse_a-ellipse_b-ellipse_c-ellipse_d;

    _a_b_cd = ellipse_d-ellipse_a-ellipse_b-ellipse_c;

    _a_bc_d = ellipse_c-ellipse_a-ellipse_b-ellipse_d;

    _a_bcd = ellipse_c.intersected(ellipse_d)-ellipse_a-ellipse_b;

    _ab_c_d = ellipse_b-ellipse_a-ellipse_c-ellipse_d;

    _ab_cd = ellipse_b.intersected(ellipse_d)-ellipse_a-ellipse_c;

    _abc_d = ellipse_b.intersected(ellipse_c)-ellipse_a-ellipse_d;

    _abcd = (ellipse_b.intersected(ellipse_c)).intersected(ellipse_d)-ellipse_a;

    a_b_c_d = ellipse_a-ellipse_b-ellipse_c-ellipse_d;

    a_b_cd = ellipse_a.intersected(ellipse_d)-ellipse_b-ellipse_c;

    a_bc_d = ellipse_a.intersected(ellipse_c)-ellipse_b-ellipse_d;

    a_bcd = (ellipse_a.intersected(ellipse_c)).intersected(ellipse_d)-ellipse_b;

    ab_c_d = ellipse_a.intersected(ellipse_b)-ellipse_c-ellipse_d;

    ab_cd = (ellipse_a.intersected(ellipse_b)).intersected(ellipse_d)-ellipse_c;

    abc_d = (ellipse_a.intersected(ellipse_b)).intersected(ellipse_c)-ellipse_d;

    abcd = ((ellipse_a.intersected(ellipse_b)).intersected(ellipse_c)).intersected(ellipse_d);

    pen.setWidth(5);
    pen.setColor(Qt::white);
    term_color = QColor(0,255,255,210);
    dont_care_color = QColor(255,247,0,190);
    min_term_color = QColor(0,255,9,50);

}

void MainWindow::draw_skeleton(){
    scene.addPath(rect, pen);
    scene.addPath(ellipse_a, pen);
    scene.addPath(ellipse_b,pen);
    scene.addPath(ellipse_c,pen);
    scene.addPath(ellipse_d,pen);

}

void MainWindow::draw_term(int term, QColor color){
    switch (term) {
        case 0: scene.addPath(_a_b_c_d,pen,color); break;
        case 1: scene.addPath(_a_b_cd,pen,color); break;
        case 2: scene.addPath(_a_bc_d,pen,color); break;
        case 3: scene.addPath(_a_bcd,pen,color); break;
        case 4: scene.addPath(_ab_c_d,pen,color); break;
        case 5: scene.addPath(_ab_cd,pen,color); break;
        case 6: scene.addPath(_abc_d,pen,color); break;
        case 7: scene.addPath(_abcd,pen,color); break;
        case 8: scene.addPath(a_b_c_d,pen,color); break;
        case 9: scene.addPath(a_b_cd,pen,color); break;
        case 10: scene.addPath(a_bc_d,pen,color); break;
        case 11: scene.addPath(a_bcd,pen,color); break;
        case 12: scene.addPath(ab_c_d,pen,color); break;
        case 13: scene.addPath(ab_cd,pen,color); break;
        case 14: scene.addPath(abc_d,pen,color); break;
        case 15: scene.addPath(abcd,pen,color); break;
    }
}

void MainWindow::draw_solution(vector<int> solution){
    /**
    sort(solution.begin(), solution.end());
    solution.erase(unique(solution.begin(), solution.end()), solution.end());
    for(auto i : solution){
        cout << i << endl;
        draw_term(i, QColor(130+qrand()%120,255,130+qrand()%120, 120));
    }
    */
}



void MainWindow::on_pushButton_zeige_minimierte_darstellung_clicked()
{
    scene.clear();
    draw_skeleton();
    //draw_solution(global_answer_terms);
    draw_all_terms();
}

void MainWindow::on_pushButton_clear_clicked()
{
    scene.clear();
    draw_skeleton();
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    global_answer.clear();
    global_answer_terms.clear();
}

void MainWindow::clear_scene(){
    scene.clear();
    draw_skeleton();
}
