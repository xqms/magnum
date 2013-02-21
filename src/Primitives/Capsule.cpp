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

#include "Capsule.h"

#include "Math/Functions.h"
#include "Math/Vector3.h"

namespace Magnum { namespace Primitives {

Capsule::Capsule(std::uint32_t hemisphereRings, std::uint32_t cylinderRings, std::uint32_t segments, GLfloat length, TextureCoords textureCoords): MeshData3D(Mesh::Primitive::Triangles, new std::vector<std::uint32_t>, {new std::vector<Vector3>()}, {new std::vector<Vector3>()}, textureCoords == TextureCoords::Generate ? std::vector<std::vector<Vector2>*>{new std::vector<Vector2>()} : std::vector<std::vector<Vector2>*>()), segments(segments), textureCoords(textureCoords) {
    CORRADE_ASSERT(hemisphereRings >= 1 && cylinderRings >= 1 && segments >= 3, "Capsule must have at least one hemisphere ring, one cylinder ring and three segments", );

    GLfloat height = 2.0f+length;
    GLfloat hemisphereTextureCoordsVIncrement = 1.0f/(hemisphereRings*height);
    Rad hemisphereRingAngleIncrement = Rad(Constants::pi())/(2*hemisphereRings);

    /* Bottom cap vertex */
    capVertex(-height/2, -1.0f, 0.0f);

    /* Rings of bottom hemisphere */
    hemisphereVertexRings(hemisphereRings-1, -length/2, -Rad(Constants::pi())/2+hemisphereRingAngleIncrement, hemisphereRingAngleIncrement, hemisphereTextureCoordsVIncrement, hemisphereTextureCoordsVIncrement);

    /* Rings of cylinder */
    cylinderVertexRings(cylinderRings+1, -length/2, length/cylinderRings, 1.0f/height, length/(cylinderRings*height));

    /* Rings of top hemisphere */
    hemisphereVertexRings(hemisphereRings-1, length/2, hemisphereRingAngleIncrement, hemisphereRingAngleIncrement, (1.0f + length)/height+hemisphereTextureCoordsVIncrement, hemisphereTextureCoordsVIncrement);

    /* Top cap vertex */
    capVertex(height/2, 1.0f, 1.0f);

    /* Faces */
    bottomFaceRing();
    faceRings(hemisphereRings*2-2+cylinderRings);
    topFaceRing();
}

Capsule::Capsule(std::uint32_t segments, TextureCoords textureCoords): MeshData3D(Mesh::Primitive::Triangles, new std::vector<std::uint32_t>, {new std::vector<Vector3>()}, {new std::vector<Vector3>()}, textureCoords == TextureCoords::Generate ? std::vector<std::vector<Vector2>*>{new std::vector<Vector2>()} : std::vector<std::vector<Vector2>*>()), segments(segments), textureCoords(textureCoords) {}

void Capsule::capVertex(GLfloat y, GLfloat normalY, GLfloat textureCoordsV) {
    positions(0)->push_back({0.0f, y, 0.0f});
    normals(0)->push_back({0.0f, normalY, 0.0f});

    if(textureCoords == TextureCoords::Generate)
        textureCoords2D(0)->push_back({0.5, textureCoordsV});
}

void Capsule::hemisphereVertexRings(std::uint32_t count, GLfloat centerY, Rad startRingAngle, Rad ringAngleIncrement, GLfloat startTextureCoordsV, GLfloat textureCoordsVIncrement) {
    Rad segmentAngleIncrement = 2*Rad(Constants::pi())/segments;
    GLfloat x, y, z;
    for(std::uint32_t i = 0; i != count; ++i) {
        Rad ringAngle = startRingAngle + i*ringAngleIncrement;
        x = z = Math::cos(ringAngle);
        y = Math::sin(ringAngle);

        for(std::uint32_t j = 0; j != segments; ++j) {
            Rad segmentAngle = j*segmentAngleIncrement;
            positions(0)->push_back({x*Math::sin(segmentAngle), centerY+y, z*Math::cos(segmentAngle)});
            normals(0)->push_back({x*Math::sin(segmentAngle), y, z*Math::cos(segmentAngle)});

            if(textureCoords == TextureCoords::Generate)
                textureCoords2D(0)->push_back({j*1.0f/segments, startTextureCoordsV + i*textureCoordsVIncrement});
        }

        /* Duplicate first segment in the ring for additional vertex for texture coordinate */
        if(textureCoords == TextureCoords::Generate) {
            positions(0)->push_back((*positions(0))[positions(0)->size()-segments]);
            normals(0)->push_back((*normals(0))[normals(0)->size()-segments]);
            textureCoords2D(0)->push_back({1.0f, startTextureCoordsV + i*textureCoordsVIncrement});
        }
    }
}

void Capsule::cylinderVertexRings(std::uint32_t count, GLfloat startY, GLfloat yIncrement, GLfloat startTextureCoordsV, GLfloat textureCoordsVIncrement) {
    Rad segmentAngleIncrement = 2*Rad(Constants::pi())/segments;
    for(std::uint32_t i = 0; i != count; ++i) {
        for(std::uint32_t j = 0; j != segments; ++j) {
            Rad segmentAngle = j*segmentAngleIncrement;
            positions(0)->push_back({Math::sin(segmentAngle), startY, Math::cos(segmentAngle)});
            normals(0)->push_back({Math::sin(segmentAngle), 0.0f, Math::cos(segmentAngle)});

            if(textureCoords == TextureCoords::Generate)
                textureCoords2D(0)->push_back({j*1.0f/segments, startTextureCoordsV + i*textureCoordsVIncrement});
        }

        /* Duplicate first segment in the ring for additional vertex for texture coordinate */
        if(textureCoords == TextureCoords::Generate) {
            positions(0)->push_back((*positions(0))[positions(0)->size()-segments]);
            normals(0)->push_back((*normals(0))[normals(0)->size()-segments]);
            textureCoords2D(0)->push_back({1.0f, startTextureCoordsV + i*textureCoordsVIncrement});
        }

        startY += yIncrement;
    }
}

void Capsule::bottomFaceRing() {
    for(std::uint32_t j = 0; j != segments; ++j) {
        /* Bottom vertex */
        indices()->push_back(0);

        /* Top right vertex */
        indices()->push_back((j != segments-1 || textureCoords == TextureCoords::Generate) ?
            j+2 : 1);

        /* Top left vertex */
        indices()->push_back(j+1);
    }
}

void Capsule::faceRings(std::uint32_t count, std::uint32_t offset) {
    std::uint32_t vertexSegments = segments + (textureCoords == TextureCoords::Generate ? 1 : 0);

    for(std::uint32_t i = 0; i != count; ++i) {
        for(std::uint32_t j = 0; j != segments; ++j) {
            std::uint32_t bottomLeft = i*vertexSegments+j+offset;
            std::uint32_t bottomRight = ((j != segments-1 || textureCoords == TextureCoords::Generate) ?
                i*vertexSegments+j+1+offset : i*segments+offset);
            std::uint32_t topLeft = bottomLeft+vertexSegments;
            std::uint32_t topRight = bottomRight+vertexSegments;

            indices()->push_back(bottomLeft);
            indices()->push_back(bottomRight);
            indices()->push_back(topRight);
            indices()->push_back(bottomLeft);
            indices()->push_back(topRight);
            indices()->push_back(topLeft);
        }
    }
}

void Capsule::topFaceRing() {
    std::uint32_t vertexSegments = segments + (textureCoords == TextureCoords::Generate ? 1 : 0);

    for(std::uint32_t j = 0; j != segments; ++j) {
        /* Bottom left vertex */
        indices()->push_back(normals(0)->size()-vertexSegments+j-1);

        /* Bottom right vertex */
        indices()->push_back((j != segments-1 || textureCoords == TextureCoords::Generate) ?
            normals(0)->size()-vertexSegments+j : normals(0)->size()-segments-1);

        /* Top vertex */
        indices()->push_back(normals(0)->size()-1);
    }
}

}}
