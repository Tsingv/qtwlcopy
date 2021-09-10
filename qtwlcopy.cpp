#include <QApplication>
#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QKeyEvent>
#include <iostream>
#include <string>
#include <unistd.h>

class win:public QDialog{
    public:
        QVBoxLayout *vbox = NULL;
        QLineEdit *input = NULL;
        QApplication *app = NULL;
        win(QApplication *a){
            app = a;
            vbox = new QVBoxLayout();
            input = new QLineEdit();
            vbox->addWidget(input);
            setLayout(vbox);
            setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint );
            setMinimumWidth(400);
            setMinimumHeight(50);
            setMaximumWidth(400);
            setMaximumHeight(50);
            setWindowTitle("qtwlcopy");
        }

        void keyPressEvent(QKeyEvent *e){
            // std::cout << e->key() << std::endl;
            if(e->key() == 0x1000000){
                // std::cout << "ESC pressed" << std::endl;
                app->exit(0);
            }
            if(e->key() == 0x1000004){
                // std::cout << "Enter pressed" << std::endl;
                save2wlcopy(input->text().toStdString());
                app->exit(0);
            }
        }

    private:
        void save2wlcopy(std::string s){
            std::string filename = "/tmp/qtwlcopyTEMP";
            FILE *fp;
            FILE *tmp = fopen(filename.c_str(), "wb+");
            std::string command = "wl-copy < " + filename ;
            fwrite(s.c_str(), s.length()+1, 1, tmp);
            fclose(tmp);
            if (NULL==(fp = popen(command.c_str(),"r"))){
                perror("wl-copy failed!");
                app->exit(1);
            }
            pclose(fp);
            unlink(filename.c_str());
        }
};

int main(int argc, char *argv[])
{
    QApplication *app = new QApplication(argc, argv);
    win *w = new win(app);
    QPoint pos = w->pos();
    if(pos.x() < 0) pos.setX(0);
    if(pos.y() < 0) pos.setY(0);
    w->move(pos);
    w->show();
    return app->exec();
}
