#include "cppfan/cppfan.h"

CF_USING_NAMESPACE
CF_BEGIN_TEST_GROUP(MemoryTest)

class MemoryTestSuperObj : public Object {
public:
  int val;
  MemoryTestSuperObj() { puts("superObj ctor"); }
  ~MemoryTestSuperObj() { puts("superObj dector"); }
};

class MemoryTestObj : public MemoryTestSuperObj {
public:
  int val2;
  MemoryTestObj() { puts("Obj ctor"); }
  ~MemoryTestObj() { puts("Obj dector"); }
};


CF_DEF_TEST(testMemAlloc){
  char *m = (char *)cf_malloc(10);
  cf_dumpMem();
  cf_free(m);
}

CF_DEF_TEST(testNew){
  MemoryTestObj *obj = new MemoryTestObj();
  MemoryTestObj *obj3 = CF_NEW MemoryTestObj();

  MemoryTestObj *obj4 = new MemoryTestObj[2];
  MemoryTestObj *obj6 = CF_NEW MemoryTestObj[2];
  cf_dumpMem();
  delete obj;
  delete obj3;
  delete[] obj4;
  delete[] obj6;
}

CF_DEF_TEST(testPlacementNew){
  char buffer[256];
  char buffer2[256];
  MemoryTestObj *obj2 = new (buffer) MemoryTestObj();
  MemoryTestObj *obj5 = new (buffer2) MemoryTestObj[2];
  cf_dumpMem();
  puts("-------");
  obj2->~MemoryTestObj();
  puts("-------");
  obj5->~MemoryTestObj();
  puts("-------");
  (obj5+1)->~MemoryTestObj();
  puts("-------");
}

CF_DEF_TEST(testMemPool){
  MemPool pool(256, 10);
  cf_dumpMem();
}

CF_END_TEST_GROUP
