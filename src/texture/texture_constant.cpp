/*
	Lightmetrica - Copyright (c) 2019 Hisanari Otsu
	Distributed under MIT license. See LICENSE file for details.
*/

#include <pch.h>
#include <lm/core.h>
#include <lm/texture.h>

LM_NAMESPACE_BEGIN(LM_NAMESPACE)

class Texture_Constant final : public Texture {
private:
	Vec3 color_;

public:
	LM_SERIALIZE_IMPL(ar) {
		ar(color_);
	}

public:
	virtual void construct(const Json& prop) override {
		color_ = json::value<Vec3>(prop, "color");
	}
	
	virtual TextureSize size() const override {
		return { 1,1 };
	}

	virtual Vec3 eval(Vec2) const override {
		return color_;
	}

	virtual Vec3 eval_by_pixel_coords(int, int) const override {
		return color_;
	}
};

LM_COMP_REG_IMPL(Texture_Constant, "texture::constant");

LM_NAMESPACE_END(LM_NAMESPACE)
