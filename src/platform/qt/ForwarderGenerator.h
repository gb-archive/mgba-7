/* Copyright (c) 2013-2022 Jeffrey Pfau
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */
#pragma once

#include <QByteArray>
#include <QImage>
#include <QObject>
#include <QString>
#include <QVector>

#include <memory>

namespace QGBA {

class ForwarderGenerator : public QObject {
Q_OBJECT

public:
	enum class System {
		N3DS,
		VITA,
	};

	static std::unique_ptr<ForwarderGenerator> createForSystem(System);

	void setTitle(const QString& title) { m_title = title; }
	void setRom(const QString& path) { m_romPath = path; }
	void setImage(int index, const QImage&);

	QString title() const { return m_title; }
	QString rom() const { return m_romPath; }
	QImage image(int index) const;

	QByteArray hashRom() const;

	virtual QList<QPair<QString, QSize>> imageTypes() const = 0;
	virtual System system() const = 0;
	QString systemName() const { return systemName(system()); }
	virtual QString extension() const = 0;

	static QString systemName(System);

	virtual bool rebuild(const QString& source, const QString& target) = 0;

protected:
	ForwarderGenerator(int imageTypes, QObject* parent = nullptr);

private:
	QString m_title;
	QString m_romPath;
	QVector<QImage> m_images;
};

}
