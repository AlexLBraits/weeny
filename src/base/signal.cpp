#include <base/signal.h>

std::map<size_t, BaseSignal*> BaseSignal::_reestr;
size_t BaseSignal::_handlerGenerator = 0;

BaseSignal::BaseSignal() : _handler(++_handlerGenerator) {
    BaseSignal::_reestr[_handler] = this;
}

BaseSignal::~BaseSignal() {
    BaseSignal::_reestr.erase(_handler);
}

BaseSignal *BaseSignal::getSignal(size_t hadler) {
    auto it = _reestr.find(hadler);
    if (it == _reestr.end()) return 0;
    return it->second;
}

size_t BaseSignal::disconnect(size_t) {
    return 0;
}

Connection::Connection(size_t signalHandler, size_t slotId)
    : _signalHandler(signalHandler),
      _slotId(slotId)
{
}

Connection::~Connection()
{
    disconnect();
}

size_t Connection::slotId() const
{
    return _slotId;
}

size_t Connection::disconnect()
{
    BaseSignal* signal = BaseSignal::getSignal(_signalHandler);
    if(signal)
    {
        return signal->disconnect(_slotId);
    }
    return 0;
}
