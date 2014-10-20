#include "renderarea.h"
#include "mainwindow.h"
#include <QtWidgets>

//! [0]
const int IdRole = Qt::UserRole;
//! [0]

//! [1]
DrawPart::DrawPart()
{

    QRect rec = QApplication::desktop()->screenGeometry();
     int height = rec.height()*0.8;
     int width = rec.width()*0.8;
    this->setFixedSize(width,height);

    renderArea = new RenderArea;

    QGridLayout *mainLayout = new QGridLayout;
//! [9] //! [10]
    mainLayout->setColumnStretch(0, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->addWidget(renderArea, 0, 0, 1, 4);
    setLayout(mainLayout);

    //draw
    this->setWindowTitle( tr("Basic Drawing"));
}
