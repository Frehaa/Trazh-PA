#include "http_alerter.h"

#include <QTimer>
#include <QtConcurrentRun>

HttpAlerter::HttpAlerter(QObject *parent) : requester(), doc(), requestData("")
{
	//	Watcher used for calling _processRequest once _newRequest has finished when called from _createAsyncRequest
	this->watcher = new QFutureWatcher<void>(this);
	QObject::connect(watcher, SIGNAL(finished()), this, SLOT(_processRequest()));

	//	Overwriting HttpRequesters writeCallback which handles how the streamed data is handled
	this->requester.setWriteCallback(&requestData, HttpAlerter::_requestCallback);

	//	Temporary solution to adding search words
	this->_getSearchWords();
}
 
HttpAlerter::~HttpAlerter()
{}

void HttpAlerter::newAlert()
{
	this->_createAsyncRequest();

	//	Starts a timer which repeatedly calls _createAsyncRequest
	QTimer *timer = new QTimer(this);
	QObject::connect(timer, SIGNAL(timeout()), this, SLOT(_createAsyncRequest()));
	timer->start(10000);
}

void HttpAlerter::_createAsyncRequest()
{
	QFuture<void> future = QtConcurrent::run(this, &HttpAlerter::_newRequest);
	this->watcher->setFuture(future);
}

void HttpAlerter::_processRequest()
{
	qDebug() << "\nStart proccesing";

	auto items = this->_xmlFindItems();
	if (items.length() == 0)
	{
		qDebug() << "No items. Stopping "<< __func__;
		return;
	}

	qDebug() << "Items before repeat filter:" << items.length();

	this->_filterRepeats(items);
	
	qDebug() << "Items after repeat filter:" << items.length();

	qDebug() << "\t\tWord filter";

	this->_filterSearchWords(items);

	qDebug() << "Items after word filter:" << items.length();
	
	QString docStr = this->doc.toString();

	emit mySignal(items);
}

void HttpAlerter::_newRequest()
{
	this->requestData.clear();
	this->requester.newRequest("http://content.warframe.com/dynamic/rss.php");
}

QDomNodeList HttpAlerter::_xmlFindItems()
{
	if (!doc.setContent(requestData))
	{
		qDebug() << "Failed to set content";
		return QDomNodeList();
	}
	
	auto root = doc.firstChildElement();
	if (root.isNull())
	{
		qDebug() << "Root is null";
		return QDomNodeList();
	}

	auto channel = root.firstChildElement("channel");
	if (channel.isNull())
	{
		qDebug() << "Channel is null";
		return QDomNodeList();
	}


	return channel.elementsByTagName("item");	
}

void HttpAlerter::_filterRepeats(QDomNodeList list)
{
	auto item = list.item(0);

	auto tempGuidList = guidList;

	//	Loop through the items by siblings. Continue as long as nextSibling is not null
	while (!item.isNull())
	{
		QString guid = item.firstChildElement("guid").text(),
			text = item.firstChildElement("title").text();

		qDebug() << "Proccesing:\t" << guid << " : " << text;

		//	Sibling element for next iteration
		auto sibling = item.nextSiblingElement("item");

		//	See if this item's guid is in the guid list
		//	if it is remove the item from parent dom node and move on to next sibling 
		//	also remove the guid from the temp list since the item it points to has now been processed
		auto findIt = tempGuidList.find(guid);

		if (findIt != tempGuidList.end())
		{
			qDebug() << "Removing:\t" << guid << " : " << text;
			auto removedChild = item.parentNode().removeChild(item);
			if (removedChild.isNull())
				qDebug() << "Shit went wrong: Node not removed from parent.";
			tempGuidList.erase(findIt);
		}
		//	If no guid matches we add this item's guid to the guid list
		else
		{
			guidList.insert(guid);
		}

		//	Progress to next sibling
		item = sibling;
	}
}

void HttpAlerter::_filterSearchWords(QDomNodeList list)
{
	auto item = list.item(0);
	
	//	Loop through the items by siblings. Continue as long as nextSibling is not null
	while (!item.isNull())
	{
		QString guid = item.firstChildElement("guid").text(),
			text = item.firstChildElement("title").text();

		qDebug() << "Proccesing:\t" << guid << " : " << text;

		//	Sibling element for next iteration
		auto sibling = item.nextSiblingElement("item");

		bool isWantedItem = false;

		for (auto it = searchWords.begin(); it != searchWords.end(); ++it)
		{
			auto word = *it;
			if (text.contains(*it, Qt::CaseInsensitive))
			{
				isWantedItem = true;
				break;
			}
		}

		if (!isWantedItem)
		{
			qDebug() << "Removing:\t" << guid << " : " << text;
			auto removedChild = item.parentNode().removeChild(item);
			if (removedChild.isNull())
				qDebug() << "Shit went wrong: Node not removed from parent.";
		}

		//	Progress to next sibling
		item = sibling;
	}
}

void HttpAlerter::_getSearchWords()
{
	//	Temp code before implementing a file read version
	this->searchWords.insert("Catalyst");
	this->searchWords.insert("Reactor");
	this->searchWords.insert("Forma");
	this->searchWords.insert("Skin");
	this->searchWords.insert("Muta");
}

size_t HttpAlerter::_requestCallback(char *buffer, size_t size, size_t itemCount, void *userdata)
{
	size_t realSize = size * itemCount;
	auto qString = static_cast<QString*>(userdata);
	
	qString->append(buffer);
	
	return realSize;
}

void HttpAlerter::addSearchWord(QString word)
{
	this->searchWords.insert(word);
}

QSet<QString> HttpAlerter::getSearchWords()
{
	return this->searchWords;
}