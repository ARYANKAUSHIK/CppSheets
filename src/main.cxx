#include <QApplication>
#include <QFile>
#include <QTextStream>

#include "window.hh"

int main(int argc, char **argv) {
    QApplication app(argc,argv);

    QFile css(":/style.css");
    QString style = "";
    if (css.open(QFile::ReadOnly)) {
        QTextStream reader(&css);
        while (!reader.atEnd()) {
            style+=reader.readLine();
        }
        css.close();
    }

    Window win;
    win.setStyleSheet(style);
    win.show();

    return app.exec();
}
