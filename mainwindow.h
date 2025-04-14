#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>
#include <random>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SetRandomGen(const std::mt19937& random_gen);

private slots:

    void on_pop_back_clicked();

    void on_push_back_clicked();

    void on_clear_clicked();

    void on_list_widget_currentRowChanged(int currentRow);

    void on_erase_clicked();

    void on_insert_clicked();

    void on_iter_minus_pb_clicked();

    void on_iter_plus_pb_clicked();

    void on_iter_begin_pb_clicked();

    void on_iter_end_pb_clicked();

    void on_edit_pb_clicked();

    void on_resize_clicked();

    void on_find_clicked();

    void on_count_clicked();

    void on_min_element_clicked();

    void on_max_element_clicked();

    void on_sort_clicked();

    void on_sOrT_clicked();

    void on_unique_clicked();

    void on_reverse_clicked();

    void on_shuffle_clicked();

    void on_pop_front_clicked();

    void on_push_front_clicked();

    void on_lower_bound_btn_clicked();

    void on_upper_bound_btn_clicked();

    void on_tea_pb_clicked();

    void on_cakes_pb_clicked();

private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model deque_model_;
    Ui::MainWindow *ui;
    std::mt19937 gen_shuffle_;
};
