#include "registeruserform.h"
#include "ui_registeruserform.h"

RegisterUserForm::RegisterUserForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterUserForm)
{
    ui->setupUi(this);
    this->setFixedSize(Config::popupWidth, Config::popupHeight);
    QPoint p = this->mapToGlobal(
                QPoint(Config::width, Config::height)
                ) - QPoint(
                    this->size().width(),
                    this->size().height()
                ) - Config::popupDeviation;
    this->move(p);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    this->connect(this, SIGNAL(windowClosing()), this, SLOT(on_exit()));
}

RegisterUserForm::~RegisterUserForm()
{
    delete ui;
}

void RegisterUserForm::on_registerButton_clicked()
{
    QUrl url(QString::fromStdString(Config::registerUrl));
    QNetworkRequest req(url);
    req = Tokenizer::tokenize(req);
    QJsonObject obj;
    obj.insert("role", "USER");
    obj.insert("username", ui->usernameEdit->text());
    obj.insert("password", ui->passwordEdit->text());
    QJsonDocument doc(obj);
    auto reply = Network::instance().post(req, doc.toJson());
    QEventLoop loop;
    connect(&Network::instance(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    QColor col;
    if (!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        col = Qt::green;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->registerButton->setStyleSheet(qss);
    }
    else
    {
        col = Qt::red;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->registerButton->setStyleSheet(qss);
    }
    reply->deleteLater();
}

void RegisterUserForm::closeEvent(QCloseEvent* event)
{
    emit windowClosing();
    event->accept();
}

void RegisterUserForm::on_exit()
{
    ui->registerButton->setStyleSheet("");
    ui->usernameEdit->setText("");
    ui->passwordEdit->setText("");
    ui->usernameEdit->setFocus();
}
