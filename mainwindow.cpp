#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <algo.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    auto preserve_iter = deque_model_.iterator;
    ui->list_widget->clear();
    for(size_t i = 0; i < deque_model_.items.size(); ++i) {
        ui->list_widget->addItem(QString("%1: %2").arg(i).arg(QString::fromStdString(deque_model_.items[i])));
    }
    ui->list_widget->addItem("end");
    deque_model_.iterator = preserve_iter;
    ui->pop_back->setDisabled(deque_model_.items.empty());
    ui->pop_front->setDisabled(deque_model_.items.empty());
    ui->txt_size->setText(QString("%1").arg(deque_model_.items.size()));
    ApplyIterator();
}

void MainWindow::ApplyIterator()
{
    int distance = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    ui->list_widget->setCurrentRow(distance);
    bool end_iter = (deque_model_.iterator == deque_model_.items.end());
    ui->edit_pb->setDisabled(end_iter);
    ui->erase->setDisabled(end_iter);
    ui->iter_plus_pb->setDisabled(end_iter);
    bool begin_iter = (deque_model_.iterator == deque_model_.items.begin());
    ui->iter_minus_pb->setDisabled(begin_iter);
    if (end_iter) {
        ui->txt_elem_content->setText("");
    } else {
        auto contains = *deque_model_.iterator;
        ui->txt_elem_content->setText(QString::fromStdString(contains));
    }
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen){
    gen_shuffle_ = random_gen;
}

void MainWindow::on_pop_back_clicked()
{
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_push_back_clicked()
{
    deque_model_.items.push_back(ui->txt_elem_content->text().toUtf8().constData());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_clear_clicked()
{
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    currentRow = std::clamp(currentRow, 0, (int)deque_model_.items.size());
    deque_model_.iterator = deque_model_.items.begin() + currentRow;
    ApplyIterator();
}


void MainWindow::on_erase_clicked()
{
    deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_insert_clicked()
{
    std::string str = ui->txt_elem_content->text().toUtf8().constData();
    deque_model_.items.insert(deque_model_.iterator, str);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_iter_minus_pb_clicked()
{
    deque_model_.iterator--;
    ApplyIterator();
}


void MainWindow::on_iter_plus_pb_clicked()
{
    deque_model_.iterator++;
    ApplyIterator();
}


void MainWindow::on_iter_begin_pb_clicked()
{
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}


void MainWindow::on_iter_end_pb_clicked()
{
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}


void MainWindow::on_edit_pb_clicked()
{
    *deque_model_.iterator = ui->txt_elem_content->text().toUtf8().constData();
    ApplyModel();
}


void MainWindow::on_resize_clicked()
{
    deque_model_.items.resize(ui->txt_size->text().toInt());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_find_clicked()
{
    auto it = std::find(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toUtf8().constData());
    deque_model_.iterator = it;
    ApplyIterator();
}


void MainWindow::on_count_clicked()
{
    int sum = std::count(deque_model_.items.begin(), deque_model_.items.end(), ui->le_count->text().toUtf8().constData());
    ui->lbl_count->setText(QString("%1").arg(sum));
}


void MainWindow::on_min_element_clicked()
{
    auto it = std::min_element(deque_model_.items.begin(), deque_model_.items.end());
    deque_model_.iterator = it;
    ApplyIterator();
}


void MainWindow::on_max_element_clicked()
{
    auto it = std::max_element(deque_model_.items.begin(), deque_model_.items.end());
    deque_model_.iterator = it;
    ApplyIterator();
}


void MainWindow::on_sort_clicked()
{
    deque_model_.items = MergeSort(deque_model_.items, [](std::string left_str, std::string right_str){return QString::compare(QString::fromStdString(left_str), QString::fromStdString(right_str), Qt::CaseSensitive) < 0;});
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_sOrT_clicked()
{
    deque_model_.items = MergeSort(deque_model_.items, [](std::string left_str, std::string right_str){return QString::compare(QString::fromStdString(left_str), QString::fromStdString(right_str), Qt::CaseInsensitive) < 0;});
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_unique_clicked()
{
    if(!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }
    auto to_del = std::unique(deque_model_.items.begin(), deque_model_.items.end());
    deque_model_.items.erase(to_del, deque_model_.items.end());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_reverse_clicked()
{
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}


void MainWindow::on_shuffle_clicked()
{
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), gen_shuffle_);
    ApplyModel();
}


void MainWindow::on_pop_front_clicked()
{
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_push_front_clicked()
{
    deque_model_.items.push_front(ui->txt_elem_content->text().toUtf8().constData());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_lower_bound_btn_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        deque_model_.iterator = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toUtf8().constData());
        ApplyIterator();
    }
}


void MainWindow::on_upper_bound_btn_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        deque_model_.iterator = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), ui->txt_elem_content->text().toUtf8().constData());
        ApplyIterator();
    }
}


void MainWindow::on_tea_pb_clicked()
{
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_cakes_pb_clicked()
{
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

