/*
    Copyright © 2010, 2011, 2012 Vladimír Vondruš <mosra@centrum.cz>

    This file is part of Magnum.

    Magnum is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 3
    only, as published by the Free Software Foundation.

    Magnum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License version 3 for more details.
*/

#include "Cube.h"

#include "Math/Vector3.h"
#include "Trade/MeshData3D.h"

namespace Magnum { namespace Primitives {

Trade::MeshData3D Cube::solid() {
    return Trade::MeshData3D(Mesh::Primitive::Triangles, new std::vector<std::uint32_t>{
         0,  1,  2,  0,  2,  3, /* +Z */
         4,  5,  6,  4,  6,  7, /* +X */
         8,  9, 10,  8, 10, 11, /* +Y */
        12, 13, 14, 12, 14, 15, /* -Z */
        16, 17, 18, 16, 18, 19, /* -Y */
        20, 21, 22, 20, 22, 23  /* -X */
    }, {new std::vector<Vector3>{
        {-1.0f, -1.0f,  1.0f},
        { 1.0f, -1.0f,  1.0f},
        { 1.0f,  1.0f,  1.0f}, /* +Z */
        {-1.0f,  1.0f,  1.0f},

        { 1.0f, -1.0f,  1.0f},
        { 1.0f, -1.0f, -1.0f},
        { 1.0f,  1.0f, -1.0f}, /* +X */
        { 1.0f,  1.0f,  1.0f},

        {-1.0f,  1.0f,  1.0f},
        { 1.0f,  1.0f,  1.0f},
        { 1.0f,  1.0f, -1.0f}, /* +Y */
        {-1.0f,  1.0f, -1.0f},

        { 1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f},
        {-1.0f,  1.0f, -1.0f}, /* -Z */
        { 1.0f,  1.0f, -1.0f},

        {-1.0f, -1.0f, -1.0f},
        { 1.0f, -1.0f, -1.0f},
        { 1.0f, -1.0f,  1.0f}, /* -Y */
        {-1.0f, -1.0f,  1.0f},

        {-1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f,  1.0f},
        {-1.0f,  1.0f,  1.0f}, /* -X */
        {-1.0f,  1.0f, -1.0f}
    }}, {new std::vector<Vector3>{
        { 0.0f,  0.0f,  1.0f},
        { 0.0f,  0.0f,  1.0f},
        { 0.0f,  0.0f,  1.0f}, /* +Z */
        { 0.0f,  0.0f,  1.0f},

        { 1.0f,  0.0f,  0.0f},
        { 1.0f,  0.0f,  0.0f},
        { 1.0f,  0.0f,  0.0f}, /* +X */
        { 1.0f,  0.0f,  0.0f},

        { 0.0f,  1.0f,  0.0f},
        { 0.0f,  1.0f,  0.0f},
        { 0.0f,  1.0f,  0.0f}, /* +Y */
        { 0.0f,  1.0f,  0.0f},

        { 0.0f,  0.0f, -1.0f},
        { 0.0f,  0.0f, -1.0f},
        { 0.0f,  0.0f, -1.0f}, /* -Z */
        { 0.0f,  0.0f, -1.0f},

        { 0.0f, -1.0f,  0.0f},
        { 0.0f, -1.0f,  0.0f},
        { 0.0f, -1.0f,  0.0f}, /* -Y */
        { 0.0f, -1.0f,  0.0f},

        {-1.0f,  0.0f,  0.0f},
        {-1.0f,  0.0f,  0.0f},
        {-1.0f,  0.0f,  0.0f}, /* -X */
        {-1.0f,  0.0f,  0.0f}
    }}, {});
}

Trade::MeshData3D Cube::wireframe() {
    return Trade::MeshData3D(Mesh::Primitive::Lines, new std::vector<std::uint32_t>{
        0, 1, 1, 2, 2, 3, 3, 0, /* +Z */
        4, 5, 5, 6, 6, 7, 7, 4, /* -Z */
        1, 5, 2, 6,             /* +X */
        0, 4, 3, 7              /* -X */
    }, {new std::vector<Vector3>{
        {-1.0f, -1.0f,  1.0f},
        { 1.0f, -1.0f,  1.0f},
        { 1.0f,  1.0f,  1.0f},
        {-1.0f,  1.0f,  1.0f},

        {-1.0f, -1.0f, -1.0f},
        { 1.0f, -1.0f, -1.0f},
        { 1.0f,  1.0f, -1.0f},
        {-1.0f,  1.0f, -1.0f}
    }}, {}, {});
}

}}
