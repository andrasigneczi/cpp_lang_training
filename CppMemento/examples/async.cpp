#include <iostream>
#include <vector>
#include <future>
#include <thread>
#include <assert.h>
#include <algorithm>

struct Record {
    int price;
};

std::vector<Record> goods;

template<typename Pred>
Record* find_rec(std::vector<Record>& vr, int first, int last, Pred pred) {
    std::vector<Record>::iterator pr = std::find_if(vr.begin() + first, vr.begin() + last, pred);
    if(pr == vr.begin() + last) return nullptr;
    return &*pr;
}

const int grain = 500000;

template<typename Pred>
Record* pfind(std::vector<Record>& vr, Pred pred) {
    assert(vr.size() % grain == 0);

    std::vector<std::future<Record*>> res;

    for(int i = 0; i != vr.size(); i += grain) {
        res.push_back(async(find_rec<Pred>, std::ref(vr), i, i + grain, pred));
    }

    for(int i = 0; i != res.size(); ++i) {
        if(auto p = res[i].get()) return p;
    }
    return nullptr;
}

template<typename T>
int wait_for_any(std::vector<std::future<T>>& vf, std::chrono::steady_clock::duration d) {
    while(true) {
        for(int i = 0; i != vf.size(); ++i) {
            if(!vf[i].valid()) continue;
            switch(vf[i].wait_for(std::chrono::seconds{0})) {
            case std::future_status::ready: return i; break;
            case std::future_status::timeout: break;
            case std::future_status::deferred: throw std::runtime_error("wait_for_any: deferred future"); break;
            }
        }
        std::this_thread::sleep_for(d);
    }
}

template<typename T>
std::vector<T> wait_for_all(std::vector<std::future<T>>& vf) {
    std::vector<T> res;
    for(auto& x : vf) {
        res.push_back(x.get());
    }
    return res;
}

template<typename Pred>
Record* pfind_any(std::vector<Record>& vr, Pred pred) {
    assert(vr.size() % grain == 0);

    std::vector<std::future<Record*>> res;

    for(int i = 0; i != vr.size(); i += grain) {
        res.push_back(async(find_rec<Pred>, std::ref(vr), i, i + grain, pred));
    }

    for(int count = res.size(); count; --count) {
        int i = wait_for_any(res, std::chrono::microseconds{10});

        if(auto p = res[i].get()) return p;
    }
    return nullptr;
}

template<typename Pred>
std::vector<Record*> find_all_rec(std::vector<Record>& vr, int first, int last, Pred pred) {
    std::vector<Record*> res;
    for(int i = first; i < last; ++i) {
        if(pred(vr[i])) {
            res.push_back(&vr[i]);
        }
    }
    return res;
}

template<typename Pred>
std::vector<Record*> pfind_all(std::vector<Record>& vr, Pred pred) {
    assert(vr.size() % grain == 0);

    std::vector<std::future<std::vector<Record*>>> res;

    for(int i = 0; i != vr.size(); i += grain) {
        res.push_back(async(find_all_rec<Pred>, std::ref(vr), i, i + grain, pred));
    }

    std::vector<Record*> r;
    std::vector<std::vector<Record*>> ret = wait_for_all(res);
    for(auto& x : ret) {
        for(auto p : x) {
            r.push_back(p);
        }
    }
    return r;
}

std::ostream& operator<<(std::ostream& o, const Record& r) {
    o << r.price;
    return o;
}

void find_cheap_red() {
    assert(goods.size() % grain == 0);
    Record* p = pfind_any(goods, [](const Record& r) {return r.price < 0;});
    //Record* p = pfind(goods, [](const Record& r) {return r.price < 0;});
    if(p) std::cout << *p << "\n";

    //auto p = std::find_if(goods.begin(), goods.end(), [](const Record& r) {return r.price < 0;});
    //if(p != goods.end()) std::cout << *p << "\n";
}

void find_all_cheap_red() {
    assert(goods.size() % grain == 0);
    std::vector<Record*> p = pfind_all(goods, [](const Record& r) {return r.price < 0;});
    //Record* p = pfind(goods, [](const Record& r) {return r.price < 0;});
    for(auto& x : p) std::cout << *x << "\n";

    //auto p = std::find_if(goods.begin(), goods.end(), [](const Record& r) {return r.price < 0;});
    //if(p != goods.end()) std::cout << *p << "\n";
}

// task, async, future, promise, packaged_task
int main(int argc, char* argv[]) {

    std::cout << "dbg1\n";
    srand(time(0));
    std::cout << "dbg2\n";
    for(int i = 500*grain-1; i >= 0; --i) goods.push_back({rand()});
    std::cout << "dbg3\n";

    auto t1 = std::chrono::high_resolution_clock::now();
    find_cheap_red();
    //find_all_cheap_red();
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " microseconds\n";

    return 0;
}
