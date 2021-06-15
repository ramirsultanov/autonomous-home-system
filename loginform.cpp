#include "loginform.h"
#include "ui_loginform.h"

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
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
    this->ui->usernameEdit->setFocus();
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_request_finished(QNetworkReply *reply)
{
    if (reply->error() || reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
    {
        ui->textBrowser->setText(QString::fromStdString("Authentication failed. Possible cause - wrong username or password. Error code: " + std::to_string(reply->error())));
    }
    else
    {
        ui->textBrowser->setText("Already logged in");
        QByteArray res = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(res);
        tokenizer.setToken(doc.object().value("token").toString(), doc.object().value("role").toObject().value("name").toString());
        this->close();
        reply->deleteLater();
    }
}

void LoginForm::on_okButtin_clicked()
{
    QUrl url(QString::fromStdString(Config::loginUrl));
    QNetworkRequest req = QNetworkRequest(url);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject obj;
    obj.insert("username", ui->usernameEdit->text());
    obj.insert("password", ui->passwordEdit->text());
    QJsonDocument doc(obj);
    auto reply = Network::instance().post(req, doc.toJson());
    ui->textBrowser->setText("Proccessing...");
    QEventLoop loop;
    connect(&Network::instance(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    this->on_request_finished(reply);
}

void LoginForm::resetStatus()
{
    ui->textBrowser->setText("");
}
