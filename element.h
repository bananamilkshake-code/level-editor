#pragma once

#include <QString>
#include <QPixmap>

#include <memory>

class Parameter;

class Element
{
public:
	typedef QHash<QString, std::shared_ptr<Parameter>> parameters_t;

	static const QString EXTENSION;
	static const char* PICTURE_FORMAT;

	explicit Element(QString name);
	Element(QString name, QPixmap pixmap);
	~Element();

	bool usedLast(bool boundToZero);
	bool releaseOne();
	void resetLimit();

	QString getName() const;
	const QPixmap& getPixmap() const;
	const parameters_t& getParameters() const;

	void load(QString directory);
	void save(QString directory) const;

	bool isLimited() const;
	bool isUsedLast() const;
	int getLimit() const;

private:
	enum Data
	{
		Picture,
		Params
	};

	static const QHash<Data, QString> DATA_FILES;

	QString name;
	QPixmap pixmap;
	parameters_t parameters;

	int limit;
	int left;

	QString getPath(QString directory) const;
	QString getPathOf(QString directory, Data data) const;
};
