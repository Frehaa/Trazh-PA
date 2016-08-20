#pragma once

#include "http_requester.h"

#include <QObject>
#include <QFutureWatcher>
#include <QDomDocument>

#include <vector>

class HttpAlerter : public QObject
{
	Q_OBJECT

public:
	HttpAlerter(QObject *parent = 0);
	~HttpAlerter();

	void newAlert();

signals:
	void mySignal(QDomNodeList);

private:
	HttpRequester requester;
	QString requestData;
	QFutureWatcher<void> *watcher;

	QDomDocument doc;	
	QSet<QString> guidList;
	QSet<QString> searchWords;

	void _newRequest(int i);
	//	Temp function for specificly warframe xml. TO DO: Replace with a more generic version
	QDomNodeList _xmlFindItems();
	void _filterRepeats(QDomNodeList list);
	void _filterSearchWords(QDomNodeList list);
	void _getSearchWords();
	
	static size_t _requestCallback(char *buffer, size_t size, size_t itemCount, void *userdata);

private slots:
	void _createAsyncRequest();
	void _processRequest();
};
