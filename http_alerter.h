#pragma once

#include "http_requester.h"

#include <QObject>
#include <QFutureWatcher>
#include <QDomDocument>

#include <vector>

class TestHttpAlerter;

class HttpAlerter : public QObject
{
	//	Allow friendship so the testing class has access to private methods
	friend TestHttpAlerter;
	Q_OBJECT

public:
	HttpAlerter(QObject *parent = 0);
	~HttpAlerter();

	//	Set a new alert which continuously requests new data and emits a signal if any new data with matching search words is found
	void newAlert();

signals:
	//	Signal emitted when new items have been found
	void mySignal(QDomNodeList);

private:
	HttpRequester requester;
	QString requestData;
	QFutureWatcher<void> *watcher;

	QDomDocument doc;	
	QSet<QString> guidList;
	QSet<QString> searchWords;

	//	The function called by _createAsyncRequest which will be run in another thread to avoid stalling
	void _newRequest();
	//	Temp function for specificly warframe xml. TO DO: Replace with a more generic version
	//	Creates an xml document from the request data and returns a living list of the specific xml items we have searched for
	QDomNodeList _xmlFindItems();
	//	Filter the items found by _xmlFindItems for repeated items (items with guid matching one in guidList)
	void _filterRepeats(QDomNodeList list);
	//	Filter  the items found by _xmlFindItems for items with a word in it matching somethin in the searchWords set
	void _filterSearchWords(QDomNodeList list);
	//	(Should perhaps be a public function / simply add/remove searchWord)
	//	Constructor function which gets and adds search words to the searchWords set
	void _getSearchWords();
	
	//	Callback function for HttpRequster which specifies how the streamed data is handled
	static size_t _requestCallback(char *buffer, size_t size, size_t itemCount, void *userdata);

private slots:
	//	Slot repeatedly called when a new alert has been started, which calls _newRequest to run in another thread
	void _createAsyncRequest();
	//	The slot called when _newRequest has finished, which processes the request and emits a signal if new items are found
	void _processRequest();
};
