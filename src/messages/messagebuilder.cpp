#include "messagebuilder.hpp"
#include "singletons/emotemanager.hpp"
#include "singletons/resourcemanager.hpp"
#include "singletons/thememanager.hpp"

#include <QDateTime>

namespace chatterino {
namespace messages {

MessageBuilder::MessageBuilder()
    : message(new Message)
{
}

MessagePtr MessageBuilder::getMessage()
{
    return this->message;
}

void MessageBuilder::appendElement(MessageElement *element)
{
    this->message->addElement(element);
}

void MessageBuilder::appendTimestamp()
{
    this->appendTimestamp(QTime::currentTime());
}

void MessageBuilder::setHighlight(bool value)
{
    if (value) {
        this->message->addFlags(Message::Highlighted);
    } else {
        this->message->removeFlags(Message::Highlighted);
    }
}

void MessageBuilder::appendTimestamp(const QTime &time)
{
    this->appendElement(new TimestampElement(time));
}

QString MessageBuilder::matchLink(const QString &string)
{
    static QRegularExpression linkRegex("[[:ascii:]]*\\.[a-zA-Z]+\\/?[[:ascii:]]*");
    static QRegularExpression httpRegex("\\bhttps?://");

    auto match = linkRegex.match(string);

    if (!match.hasMatch()) {
        return QString();
    }

    QString captured = match.captured();

    if (!captured.contains(httpRegex)) {
        captured.insert(0, "http://");
    }

    return captured;
}

}  // namespace messages
}  // namespace chatterino
