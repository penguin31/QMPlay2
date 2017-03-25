/*
	QMPlay2 is a video and audio player.
	Copyright (C) 2010-2017  Błażej Szczygieł

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU Lesser General Public License as published
	by the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU Lesser General Public License for more details.

	You should have received a copy of the GNU Lesser General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <MediaBrowser/Common.hpp>

#include <NetworkAccess.hpp>

#include <QPointer>

#include <vector>
#include <tuple>

class Wbijam : public NetworkAccess, public MediaBrowserCommon
{
	Q_OBJECT

public:
	using AnimeTuple = std::tuple<QString, QString, bool>;
	using AnimeTupleList = std::vector<AnimeTuple>;

	using AnimeInneList = QVector<QString>;
	using AnimeInnePage = QPair<QString, AnimeInneList>;
	using AnimeInnePages = QVector<AnimeInnePage>;


	Wbijam(NetworkAccess &net);
	~Wbijam() final;


	void prepareWidget(QTreeWidget *treeW) override final;


	QString getQMPlay2Url(const QString &text) const override final;

	NetworkReply *getSearchReply(const QString &text, const qint32 page) override final;
	Description addSearchResults(const QByteArray &reply, QTreeWidget *treeW) override final;

	PagesMode pagesMode() const override final;
	QStringList getPagesList() const override final;

	bool hasWebpage() const override final;
	QString getWebpageUrl(const QString &text) const override final;

	CompleterMode completerMode() const override final;
	NetworkReply *getCompleterReply(const QString &text) override final;
	QStringList getCompletions(const QByteArray &reply) override final;
	void setCompleterListCallback(const CompleterReadyCallback &callback) override final;


	QAction *getAction() const override final;

	bool convertAddress(const QString &prefix, const QString &url, const QString &param, QString *streamUrl, QString *name, QIcon *icon, QString *extension, IOController<> *ioCtrl) override final;

private slots:
	void gotAnimeList();

private:
	void maybeDownloadAnimeList();

	CompleterReadyCallback m_completerListCallback;
	QPointer<NetworkReply> m_animeListReply;
	AnimeTupleList m_animeTupleList;

	AnimeTupleList m_polecaneSeries;
	AnimeInnePages m_innePages;
	QTreeWidget *m_treeW;
	qint32 m_tupleIdx;
	qint32 m_page;
};
