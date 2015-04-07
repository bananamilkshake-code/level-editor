#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QTextStream>

static QTextStream stream;

void messageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	QString time = QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss");
	switch (type) {
	case QtDebugMsg:
		stream << "[DEBUG " << time << "]: " << msg << "\n";
		break;
	case QtWarningMsg:
		stream << "[WARNING " << time << "]: " << msg << "\n";
		break;
	case QtCriticalMsg:
		stream << "[CRITICAL  " << time << "]: " << msg << "\n";
		break;
	case QtFatalMsg:
		stream << "[FATAL  " << time << "]: " << msg << "\n";
		abort();
	}
}

int main(int argc, char *argv[])
{
	qInstallMessageHandler(messageOutput);

	QString timestamp = QDateTime::currentDateTime().toString("dd-MM-yyyy(hh-mm-ss)");
	QString logName = QString("level_editor_%1.log").arg(timestamp);

	QFile logFile(logName);
	logFile.open(QFile::WriteOnly);
	stream.setDevice(&logFile);

	QApplication a(argc, argv);
	MainWindow w;
	w.show();

	int result = a.exec();

	logFile.close();

	return result;
}
