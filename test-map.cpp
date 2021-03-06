#include "object.h"
#include "string.h"
#include "map.h"
#include <stdlib.h>

void FAIL() {   exit(1);    }
void t_true(bool p) { if (!p) FAIL(); }
void t_false(bool p) { if (p) FAIL(); }

Object* o   = new Object();
String* one = new String("1");
String* two = new String("2");
String* not_one = new String("1");
String* s1 = new String("Hello");
String* s2 = new String("World");

/**
* Does this array of object points have the object we are looking for?
* @param ol the array of pointers
* @param o the object to search for.
*/
bool in(Object** ol, Object* o, size_t len) {
  bool is_in = false;
  size_t i = 0;
  while (i != len) {
      is_in = ol[i]->equals(o) || is_in;
      i++;
  }

  return is_in;
}

void test_objects() {
  // make sure it works with regular objects...
  Map* map = new Map();
  t_true(map->size() == 0);
  map->add(o, o);
  t_true(map->size() == 1);
  t_true(map->get(o)->equals(o));
}

void test_add() {
  Map* map = new Map();
  t_true(map->size() == 0);
  map->add(one, s1);
  t_true(map->size() == 1);
  t_true(map->get(one)->equals(s1));

  // the previous key value pair is overwritten
  map->add(one, s2);
  t_true(map->get(one)->equals(s2));
  t_true(map->size() == 1);

  // add/get overwrites with different objects
  map->add(not_one, s1);
  t_true(map->get(one)->equals(s1));
  t_true(map->size() == 1);

  delete map;
}

void test_clear() {
  Map* map = new Map();
  t_true(map->size() == 0);
  map->clear();
  t_true(map->size() == 0);
  map->add(one, s1);
  map->add(two, s2);
  t_true(map->size() == 2);
  map->clear();
  t_true(map->size() == 0);

  delete map;
}

void test_copy() {
  Map* map = new Map();
  map->add(one, s1);
  map->add(two, s2);
  t_true(map->size() == 2);
  Map* map2 = map->copy();
  t_true(map2->size() == 2);
  t_true(map2->get(one)->equals(s1));
  t_true(map2->get(two)->equals(s2));
  String* s3 = new String("Hi");
  map->add(one, s3);
  t_false(map2->get(one)->equals(s3));

  delete map;
  delete map2;
}

void test_keys() {
  Map* map = new Map();
  map->add(one, s1);
  map->add(two, s2);
  Object** keys = map->keys();
  t_true(in(keys, one, 2));
  t_true(in(keys, two, 2));
  t_false(in(keys, s1, 2));
  t_false(in(keys, s2, 2));
  delete[] keys;

  // show deleting from map-> doesn't do anything.
  Object** tmp = map->keys();
  tmp[0] = s1;
  Object** nkeys = map->keys();
  t_true(in(nkeys, s1, 2));
  t_true(in(nkeys, s2, 2));
  t_false(in(nkeys, one, 2));
  t_false(in(nkeys, two, 2));

  delete[] nkeys;
  delete[] tmp;
  delete map;
}

void test_values() {
  Map* map = new Map();
  map->add(one, s1);
  map->add(two, s2);
  Objects** val = map->values();
  t_true(in(val, s1, 2));
  t_true(in(val, s2, 2));
  t_false(in(val, one, 2));
  t_false(in(val, two, 2));
  delete[] val;

  // show deleting from map->values doesn't do anything.
  Object** tmp = map->values();
  tmp[0] = one;
  Objects** nval = map->values();

  t_true(in(nval, s1, 2));
  t_true(in(nval, s2, 2));
  t_false(in(nval, one, 2));
  t_false(in(nval, two, 2));

  delete[] nval;
  delete[] tmp;
  delete map;
}

void test_pop_item() {
  Map* map = new Map();
  map->add(one, s1);
  map->add(two, s2);
  t_true(map->pop_item(one)->equals(s1));
  t_true(map->pop_item(two)->equals(s2));

  delete map;
}

void test_hash_and_equals() {
  Map* map1 = new Map();
  Map* map2 = new Map();

  t_true(map1->equals(map2));
  t_true(map2->equals(map1));
  t_true(map1->hash() == map2->hash());

  map1->add(one, s1);
  map1->add(two, s2);

  t_false(map1->equals(map2));
  t_false(map2->equals(map1));
  t_false(map1->hash() == map2->hash());

  map2->add(one, s1);
  map2->add(two, s2);

  t_true(map1->equals(map2));
  t_true(map2->equals(map1));
  t_true(map1->hash() == map2->hash());

  delete map1;
  delete map2;
}

void test_map_delete() {
  Map * m = new Map();
  m->add(one, s1);
  delete m;

  t_true(one->equals(one));
  t_true(s1->equals(s1));
}

int main() {
  test_add();
  test_clear();
  test_copy();
  test_keys();
  test_values();
  test_pop_item();
  test_hash_and_equals();
  test_objects();
  return 0;
}
