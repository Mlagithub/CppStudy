
#include "typeList.h"
#include "gtest/gtest.h"

#include <type_traits>
#include <vector>

using namespace TypeList;
using namespace TypeList::Algo;

struct TLTest : public ::testing::Test {
protected:
    void SetUp() override {}

protected:
    enum class File { ACT = 0, MSH, CFX, CGNS };
    using t0 = std::vector<int>;
    using t1 = TpList<int>;
    using t2 = TpList<char>;
    using t3 = TpList<t1, float, EmptyType, char>;
    using t4 = TpList<t0, File, float, t3, EmptyType, char, t0>;
};

TEST_F(TLTest, Initial) {}

TEST_F(TLTest, TestLength) {
    EXPECT_EQ(length<t1>::value, 1);
    EXPECT_EQ(length<t2>::value, 1);
    EXPECT_EQ(length<t3>::value, 4);
    EXPECT_EQ(length<t4>::value, 7);
}

TEST_F(TLTest, TestIndex) {
    EXPECT_EQ((Algo::index<t1, int>::value), 0);
    EXPECT_EQ((Algo::index<t3, EmptyType>::value), 2);
    EXPECT_EQ((Algo::index<t3, NullType>::value), -1);
    EXPECT_EQ((Algo::index<t3, double>::value), -1);
}

TEST_F(TLTest, TestAt) {
    EXPECT_TRUE((std::is_same<Algo::at<t1, 0>::type, int>::value));
    EXPECT_TRUE((std::is_same<Algo::at<t4, 5>::type, char>::value));
}

TEST_F(TLTest, TestJoin) {
    EXPECT_TRUE((Algo::index<Algo::join<t1, t2>::type, int>::value) == 0);
    EXPECT_TRUE((Algo::index<Algo::join<t1, t2>::type, char>::value) == 1);
    EXPECT_TRUE((Algo::index<Algo::join<t2, t1>::type, int>::value) == 1);
    EXPECT_TRUE((Algo::index<Algo::join<t2, t3>::type, t1>::value) == 1);
    EXPECT_TRUE((Algo::index<Algo::join<t2, t3>::type, char>::value) == 0);
    EXPECT_TRUE((Algo::index<Algo::join<t3, t2>::type, char>::value) == 3);
    EXPECT_TRUE((Algo::length<Algo::join<double, t3>::type>::value) == 5);
    EXPECT_TRUE((Algo::length<Algo::join<t3, double>::type>::value) == 5);
}

TEST_F(TLTest, TestInsert) {
    using t31 = TpList<int>;
    using t33 = TpList<float, t31, char>;
    using t34 = Algo::insert<t33, double, 1>::type::Head;

    EXPECT_EQ((Algo::index<Algo::insert<t1, double, 0>::type, double>::value), 0);
    EXPECT_EQ((Algo::length<Algo::insert<t3, double, 1>::type>::value), 5);
    EXPECT_EQ((Algo::index<Algo::insert<t3, double, 1>::type, int>::value), 0);
    EXPECT_EQ((Algo::index<Algo::insert<t3, double, 1>::type, double>::value), 1);
    EXPECT_EQ((Algo::index<Algo::insert<t3, double, 1>::type, float>::value), 2);
    EXPECT_EQ((Algo::index<Algo::insert<t3, double, 1>::type, EmptyType>::value), 3);
    EXPECT_EQ((Algo::index<Algo::insert<t3, double, 1>::type, char>::value), 4);
}