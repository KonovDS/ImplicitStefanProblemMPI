#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch.hpp"
#include "mesh.h"

auto Setup(int width, int height) {
  Mesh<int> mesh(width, height);
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < height; j++) {
      mesh.at(i, j) = height * i + j;
    }
  }
  return mesh;
}

TEST_CASE("Mesh left pointers test", "[mesh][mesh_pointers]") {
  {
    int width = 100, height = 100;
    auto mesh = Setup(width, height);
    CHECK(&mesh.at(0, 0) == mesh.LeftPtrRecv());
    CHECK(&mesh.at(0, height - 1) == mesh.LeftPtrRecv() + height - 1);
    CHECK(&mesh.at(1, 0) == mesh.LeftPtrSend());
    CHECK(&mesh.at(1, height - 1) == mesh.LeftPtrSend() + height - 1);
  }
  {
    int width = 10, height = 100;
    auto mesh = Setup(width, height);
    CHECK(&mesh.at(0, 0) == mesh.LeftPtrRecv());
    CHECK(&mesh.at(0, height - 1) == mesh.LeftPtrRecv() + height - 1);
    CHECK(&mesh.at(1, 0) == mesh.LeftPtrSend());
    CHECK(&mesh.at(1, height - 1) == mesh.LeftPtrSend() + height - 1);
  }
  {
    int width = 100, height = 10;
    auto mesh = Setup(width, height);
    CHECK(&mesh.at(0, 0) == mesh.LeftPtrRecv());
    CHECK(&mesh.at(0, height - 1) == mesh.LeftPtrRecv() + height - 1);
    CHECK(&mesh.at(1, 0) == mesh.LeftPtrSend());
    CHECK(&mesh.at(1, height - 1) == mesh.LeftPtrSend() + height - 1);
  }
}

TEST_CASE("Mesh right pointers test", "[mesh][mesh_pointers]") {
  {
    int width = 100, height = 100;
    auto mesh = Setup(width, height);
    CHECK(&mesh.at(width - 1,  0) == mesh.RightPtrRecv());
    CHECK(&mesh.at(width - 1,  height - 1) == (mesh.RightPtrRecv() + height - 1));
    CHECK(&mesh.at(width - 2,  0) == mesh.RightPtrSend());
    CHECK(&mesh.at(width - 2,  height - 1) == (mesh.RightPtrSend() + height - 1));
  }
  {
    int width = 10, height = 100;
    auto mesh = Setup(width, height);
    CHECK(&mesh.at(width - 1,  0) == mesh.RightPtrRecv());
    CHECK(&mesh.at(width - 1,  height - 1) == (mesh.RightPtrRecv() + height - 1));
    CHECK(&mesh.at(width - 2,  0) == mesh.RightPtrSend());
    CHECK(&mesh.at(width - 2,  height - 1) == (mesh.RightPtrSend() + height - 1));
  }
  {
    int width = 100, height = 10;
    auto mesh = Setup(width, height);
    CHECK(&mesh.at(width - 1,  0) == mesh.RightPtrRecv());
    CHECK(&mesh.at(width - 1,  height - 1) == (mesh.RightPtrRecv() + height - 1));
    CHECK(&mesh.at(width - 2,  0) == mesh.RightPtrSend());
    CHECK(&mesh.at(width - 2,  height - 1) == (mesh.RightPtrSend() + height - 1));;
  }
}

TEST_CASE("Mesh left values test", "[mesh][mesh_values]") {
  {
    int width = 100, height = 100;
    auto mesh = Setup(width, height);
    bool ok = true;
    for (int i = 0; i < mesh.BorderLen(); i++) {
      if (mesh.LeftPtrRecv()[i] != i) {
        ok = false;
        break;
      }
    }
    CHECK(ok == true);
  }
  {
    int width = 10, height = 100;
    auto mesh = Setup(width, height);
    bool ok = true;
    for (int i = 0; i < mesh.BorderLen(); i++) {
      if (mesh.LeftPtrRecv()[i] != i) {
        ok = false;
        break;
      }
    }
    CHECK(ok == true);
  }
  {
    int width = 100, height = 10;
    auto mesh = Setup(width, height);
    bool ok = true;
    for (int i = 0; i < mesh.BorderLen(); i++) {
      if (mesh.LeftPtrRecv()[i] != i) {
        ok = false;
        break;
      }
    }
    CHECK(ok == true);
  }
}

TEST_CASE("Mesh right values test", "[mesh][mesh_values]") {
  {
    int width = 100, height = 100;
    auto mesh = Setup(width, height);
    bool ok = true;
    for (int i = 0; i < mesh.BorderLen(); i++) {
      if (mesh.RightPtrRecv()[i] != (width - 1) * height + i) {
        ok = false;
        break;
      }
    }
    CHECK(ok == true);
  }
  {
    int width = 10, height = 100;
    auto mesh = Setup(width, height);
    bool ok = true;
    for (int i = 0; i < mesh.BorderLen(); i++) {
      if (mesh.RightPtrRecv()[i] != (width - 1) * height + i) {
        ok = false;
        break;
      }
    }
    CHECK(ok == true);
  }
  {
    int width = 100, height = 10;
    auto mesh = Setup(width, height);
    bool ok = true;
    for (int i = 0; i < mesh.BorderLen(); i++) {
      if (mesh.RightPtrRecv()[i] != (width - 1) * height + i) {
        ok = false;
        break;
      }
    }
    CHECK(ok == true);
  }
}