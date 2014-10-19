#ifndef SOURCE_AREA_H
#define SOURCE_AREA_H
#define MAX_SIZE   32
#define BUFF_LEN  1024
#include <QVBoxLayout>
#include <QtWidgets>

class source_area : public QVBoxLayout
{
    Q_OBJECT
public:
    explicit source_area();
    ~source_area();
    bool get_input(int *st_dis,int *st_num,int *maxdis);
    int text_from_edit(QLineEdit &ledit);
    bool read_from_file();
signals:
private:
    QLineEdit *ledit_maxdis;
    QLineEdit *ledit_stnum;
    QTableWidget *table;
    int st_dis[MAX_SIZE];
public slots:
    void on_stnm_input(const QString & stnum);
    bool digit_ensure(const QString &str);
};

#endif // SOURCE_AREA_H
