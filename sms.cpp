#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "sms.h"


QString twilio_number = "";


sms::sms(){

}


void sms::sendSMS(const QString &to, const QString &message) {
    // Create a network access manager for handling network requests
    QNetworkAccessManager *manager = new QNetworkAccessManager();

    // Define the URL for Twilio's SMS sending API endpoint
    QUrl url("https://api.twilio.com/2010-04-01/Accounts//Messages.json");

    // Create a network request object with the defined URL
    QNetworkRequest request(url);

    // Define the credentials required for Twilio API authentication
    QString credentials = "";

    // Encode the credentials in Base64 format for use in the request header
    QByteArray base64Credentials = credentials.toUtf8().toBase64();

    // Set the Authorization header in the request using the encoded credentials
    request.setRawHeader("Authorization", "Basic " + base64Credentials);

    // Construct the data to be sent as part of the POST request body
    QByteArray postData;
    postData.append("From=" + twilio_number); // Specify the sender's number
    postData.append("&To=" + to); // Specify the recipient's number
    postData.append("&Body=" + message); // Specify the content of the message

    // Set the content type of the request
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    // Send the POST request to the Twilio API endpoint with the constructed data
    QNetworkReply *reply = manager->post(request, postData);

    // Connect a slot to handle the response asynchronously
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        // Check if there was an error in the network reply
        if (reply->error() == QNetworkReply::NoError) {
            // Output a success message if no error occurred
            qDebug() << "SMS sent successfully";
        } else {
            // Output an error message if an error occurred during sending
            qDebug() << "Failed to send SMS:" << reply->errorString();
        }

        // Clean up resources by deleting the reply and the network manager objects
        reply->deleteLater();
        manager->deleteLater();
    });
}
