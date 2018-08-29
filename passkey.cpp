template<class General>
class Passkey {
private:
    explicit Passkey(General* general) {};
    friend General;
};

template<class General>
class Soldier {
public:
    Soldier() : target(0) {}

    void ExecuteOrder(Passkey<General>){
        target++;
    }

    int GetStatus(Passkey<General>) {
        return target;
    }

private:
    int target;
};

struct General {
    General() {}

    void SendOrder(Soldier<General>& soldier) {
        soldier.ExecuteOrder(Passkey<General>(this));
    }

    int LeakStatus(Soldier<General>& soldier){
        return soldier.GetStatus(Passkey<General>(this));
    }
};

int main(){
    General general{};

    Soldier<General> soldier{};
    // soldier.ExecuteOrder(Passkey<General>(&general));
    //        Error! The soldier is very good at following the command chain!

    general.SendOrder(soldier);   // ...Oh no! Notice how our general takes orders from anyone!
    return general.LeakStatus(soldier);
}
