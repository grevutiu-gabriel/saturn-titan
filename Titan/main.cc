#include "MainWindow.h"
#include "Titan.h"

int main(int argc, char *argv[])
{
    Titan app(argc, argv);
    
    QPixmap pixmap(":/images/titan.icon.png");
    QIcon icon(pixmap);
    app.setWindowIcon(icon);
    
    MainWindow w;
    w.show();
    
    return app.exec();
}
