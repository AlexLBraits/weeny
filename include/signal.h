#ifndef SIGNALS_H
#define SIGNALS_H

////////////////////////////////////////////////////////////////////////////////
///
/// Шаблон Signal
///
/// первоисточник: https://developer.gnome.org/libsigc++-tutorial/2.99/
///

#include <functional>
#include <map>

////////////////////////////////////////////////////////////////////////////////
///
/// \brief The BaseSignal class - базовый класс для всех сигналов Signal
///
/// ведёт реестр существующих сигналов
/// это нужно для того, что бы отвязать сигнал от слота
/// по инициативе слота
///
class BaseSignal
{
    friend class Connection;

    static std::map<size_t, BaseSignal*> _reestr;
    static size_t _handlerGenerator;
public:
    ///
    /// \brief BaseSignal задача конструктора сгенерировать уникальный
    /// хандлер сигнала и поместить пару <хандлер>:<указатель> в реестр
    ///
    BaseSignal();
    ///
    /// \brief ~BaseSignal виртуальный деструктор в базовом классе
    /// убирает сигнал из реестра по хэндлеру
    ///
    virtual ~BaseSignal();

private:
    ///
    /// \brief getSignal - выдаёт указатель сигнала по его хендлеру
    /// \param hadler - хендлер сигнала для поиска в реестре
    /// \return - указатель на объект-сигнал или 0 если сигнал не найден
    ///
    /// getSignal вызывают только методы дружественного класса Connection
    ///
    static BaseSignal* getSignal(size_t hadler);

protected:
    ///
    /// \brief disconnect - виртуальный метод, отключает от сигнала слот slotId
    /// \param slotId - идентификатор слота для отключения
    /// \return - возвращает количество отключенных слотов, 1 или 0
    ///
    /// в базовом классе ничего не делает;
    ///
    virtual size_t disconnect(size_t /* slotId */);
    ///
    /// \brief _handler - уникальное целое число, позволяющее найти объект
    /// класса BaseSignal в реестре сигналов
    ///
    size_t _handler;
};

////////////////////////////////////////////////////////////////////////////////
///
/// \brief The Connection class - хранит информацию о соединении,
/// хендл сигнала и идентификатор слота.
/// Создаётся при соединении сигнала и слота.
/// Возвращается методом Signal::connect.
/// ----------------------------------------------------------------------------
/// Время жизни объекта Connection должно совпадать со временем жизни слота
/// или быть меньше.
/// ----------------------------------------------------------------------------
/// Основная задача разорвать соединение при уничтожении объекта Connection.
///
class Connection {
    Connection(const Connection&) = delete;
    Connection& operator=(const Connection&) = delete;
public:
    Connection(size_t signalHandler = 0, size_t slotId = 0);
    ~Connection();
    size_t slotId() const;
    size_t disconnect();
private:
    size_t _signalHandler;
    size_t _slotId;
};
typedef std::shared_ptr<Connection> ConnectionPtr;

////////////////////////////////////////////////////////////////////////////////
///
/// \brief The Signal template class - шаблон класса Signal
///
/// Signal это объект, основная задача которого обслуживать контейнер
/// объектов типа SlotType (аналог массива указателей на функцию);
///     connect - добавляет объект SlotType в контейнер
///     disconnect - удаляет объект SlotType из контейнера
///     clear - очищает контейнер
///
/// Хранящиеся в контейнере объекты SlotType могут быть вызваны
/// с помощью operator()
///
template <typename... Args>
class Signal final : public BaseSignal
{
    static size_t _slotIdGenerator;
public:
    typedef std::function<void(Args...)> SlotType;

    void operator()(Args... args) {
        for(auto& f : _slots) f.second(args...);
    }
    ///
    /// \brief connect
    /// \param slot
    /// \return
    ///
    ConnectionPtr connect(SlotType slot) {
        size_t slotId = ++_slotIdGenerator;
        _slots[slotId] = slot;
        return ConnectionPtr(new Connection(_handler, slotId));
    }
    void clear() {
        _slots.clear();
    }
    size_t disconnect(ConnectionPtr connection) {
        return connection ? _slots.erase(connection->slotId()) : 0;
    }

protected:
    size_t disconnect(size_t slotId) override {
        return _slots.erase(slotId);
    }

private:
    std::map<size_t, SlotType> _slots;
};

template<typename... Args> size_t Signal<Args ...>::_slotIdGenerator = 0;


#endif /*SIGNALS_H*/
