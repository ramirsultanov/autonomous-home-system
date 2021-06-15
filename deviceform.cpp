#include "deviceform.h"
#include "ui_deviceform.h"

DeviceForm::DeviceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceForm)
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
    ui->nameLabel->setText("");
    setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
}

DeviceForm::~DeviceForm()
{
    delete ui;
}

void DeviceForm::setInfo()
{
    QUrl url(QString::fromStdString(Config::deviceUrl) + ui->nameLabel->text());
    QNetworkRequest req(url);
    req = Tokenizer::tokenize(req);
    auto reply = Network::instance().get(req);
    QEventLoop loop;
    connect(&Network::instance(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    devices_.clear();
    ui->listWidget->clear();
    QColor col;
    if (!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        QByteArray bytes = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(bytes);
        QJsonArray arr = doc.object().value("devices").toArray();
        auto devices = model_.getDevices();
        devices.removeAll(ui->nameLabel->text());
        if (!devices.empty())
        {
            ui->labelAllowed->setEnabled(true);
            ui->listWidget->setEnabled(true);
            ui->saveButton->setEnabled(true);
            if (Tokenizer::role == "ADMIN")
            {
                ui->removeButton->setEnabled(true);
            }
            else
            {
                ui->removeButton->setEnabled(false);
            }
            ui->labelCommand->setEnabled(true);
            ui->lineEdit->setEnabled(true);
            for (QString dev : devices)
            {
                QListWidgetItem* checkBox = new QListWidgetItem();
                devices_.append(checkBox);
                QFont font;
                font.setPointSize(12);
                checkBox->setFont(font);
                checkBox->setText(dev);
                checkBox->setCheckState(arr.contains(dev) ? Qt::Checked : Qt::Unchecked);
                if (Tokenizer::role == "USER")
                {
                    checkBox->setFlags(checkBox->flags() & ~Qt::ItemIsUserCheckable);
                }
                ui->listWidget->addItem(checkBox);
            }
            ui->listWidget->update();
        }
        else
        {
            ui->labelAllowed->setEnabled(false);
            ui->listWidget->setEnabled(false);
            ui->labelCommand->setEnabled(false);
            ui->lineEdit->setEnabled(false);
            ui->saveButton->setEnabled(false);
            ui->removeButton->setEnabled(false);
        }
        ui->saveButton->setStyleSheet("");
    }
    else
    {

        col = Qt::gray;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->saveButton->setStyleSheet(qss);
        ui->saveButton->setEnabled(false);
        ui->removeButton->setEnabled(false);
    }
    reply->deleteLater();
    if (Tokenizer::role == "ADMIN")
    {
        ui->labelAllowed->setEnabled(true);
    }
    else
    {
        ui->labelAllowed->setEnabled(false);
    }
}

void DeviceForm::setDeviceName(QString name)
{
    ui->nameLabel->setText(name);
}

void DeviceForm::setDeviceScript(QString script)
{
    ui->lineEdit->setText(script);
}

void DeviceForm::on_saveButton_clicked()
{
    QUrl url(QString::fromStdString(Config::setDeviceConfigUrl));
    QNetworkRequest req(url);
    req = Tokenizer::tokenize(req);
    QJsonObject obj;
    obj.insert("username", ui->nameLabel->text());
    obj.insert("script", ui->lineEdit->text());
    QJsonArray arr;
    for (QListWidgetItem *i : devices_)
    {
        if (i->checkState() == Qt::Checked)
        {
            arr.append(i->text());
        }
    }
    obj.insert("devices", arr);
    QJsonDocument doc(obj);
    auto reply = Network::instance().post(req, doc.toJson());
    QEventLoop loop;
    connect(&Network::instance(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    QColor col;
    if (!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        emit this->tableChanged();
        col = Qt::green;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->saveButton->setStyleSheet(qss);
    }
    else
    {
        col = Qt::red;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->saveButton->setStyleSheet(qss);
    }
}

void DeviceForm::on_removeButton_clicked()
{
    QUrl url(QString::fromStdString(Config::removeUrl));
    QNetworkRequest req(url);
    req = Tokenizer::tokenize(req);
    QJsonObject obj;
    obj.insert("devicename", ui->nameLabel->text());
    QJsonDocument doc(obj);
    auto reply = Network::instance().post(req, doc.toJson());
    QEventLoop loop;
    connect(&Network::instance(), SIGNAL(finished(QNetworkReply*)), &loop, SLOT(quit()));
    loop.exec();
    QColor col;
    if (!reply->error() && reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() == 200)
    {
        emit this->tableChanged();
        this->close();
    }
    else
    {
        col = Qt::red;
        QString qss = QString("background-color: %1").arg(col.name());
        ui->removeButton->setStyleSheet(qss);
    }
    reply->deleteLater();
}
