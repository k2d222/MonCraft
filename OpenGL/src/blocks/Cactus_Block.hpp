#pragma once

#include "Block.hpp"
#include "model/CactusModel.hpp"

class Cactus_Block : public Block {
public:
    static Cactus_Block* get() {
        static Cactus_Block inst;
        return &inst;
    }

    glm::ivec2 getFaceUVs(BlockFace face) const override {
        if (face == BlockFace::TOP || face == BlockFace::BOTTOM)
            return { 3, 0 };
        return { 4, 0 };
    }
    
    bool isOpaque() const override { return false; }

    BlockModel * getModel() const override { return CactusModel::get(); }

private:
    Cactus_Block() : Block(BlockType::Cactus) {}
};
