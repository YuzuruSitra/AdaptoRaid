#pragma once
#include <cmath>
#include <iostream>

/*3�����x�N�g��*/
//-------------//
//�E�g���� (��)
// (x, y, z) = (2.0, 3.0, 4.0)�̃x�N�g�����쐬
// vector_t v(2.0, 3.0, 4.0);
//
// �W���I��vector_t���擾
// vector_t::Zero();�@	(  0,  0,  0)
// vector_t::Up();�@	(  0,  1,  0)
// vector_t::Down();�@	(  0, -1,  0)
// vector_t::Forward(); (  0,  0, -1)
// vector_t::Back();�@	(  0,  1,  1)
// vector_t::Right();�@	(  1,  0,  0)
// vector_t::Left();�@	( -1,  0,  0)
//-------------//
struct vector_t {
	float x, y, z;

	inline vector_t() : x(0.0), y(0.0), z(0.0) {}

	inline vector_t(float _x, float _y, float _z)
		: x(_x), y(_y), z(_z) {
	}

	//�x�N�g���̑����Z
	inline vector_t operator + (vector_t& _v) {
		return vector_t(this->x + _v.x,
						this->y + _v.y,
						this->z + _v.z);
	}

	//�x�N�g���̈����Z
	inline vector_t operator - (vector_t& _v) {
		return vector_t(this->x - _v.x,
						this->y - _v.y,
						this->z - _v.z);
	}

	//�x�N�g�� * �X�J���[
	inline friend vector_t operator * (vector_t& _v, float _f) {
		return vector_t(_v.x * _f,
						_v.y * _f,
						_v.z * _f);
	}

	//�X�J���[ * �x�N�g��
	inline friend vector_t operator * (float _f, vector_t& _v) {
		return vector_t(_v.x * _f,
						_v.y * _f,
						_v.z * _f);
	}

	//�x�N�g�� / �X�J���[
	inline vector_t operator / (float _f) {
		return vector_t(this->x / _f,
						this->y / _f,
						this->z / _f);
	}

	inline vector_t& operator += (vector_t& _v) {
		this->x += _v.x;
		this->y += _v.y;
		this->z += _v.z;
		return *this;
	}

	inline vector_t& operator -= (vector_t& _v) {
		this->x -= _v.x;
		this->y -= _v.y;
		this->z -= _v.z;
		return *this;
	}

	inline vector_t& operator *= (float _f) {
		this->x *= _f;
		this->y *= _f;
		this->z *= _f;
		return *this;
	}

	inline vector_t& operator /= (float _f) {
		this->x /= _f;
		this->y /= _f;
		this->z /= _f;
		return *this;
	}


	inline friend bool operator == (vector_t _v1, vector_t _v2) {
		if (_v1.x == _v2.x && _v1.y == _v2.y && _v1.z == _v2.z) return true;
		return false;
	}

	inline friend bool operator != (vector_t _v1, vector_t _v2) {
		return !(_v1 == _v2);
	}


	//0�x�N�g��
	inline static vector_t Zero() {
		return vector_t(0.0, 0.0, 0.0);
	}

	inline static vector_t Up() {
		return vector_t(0.0, 1.0, 0.0);
	}

	inline static vector_t Down() {
		return vector_t(0.0, -1.0, 0.0);
	}

	inline static vector_t Forward() {
		return vector_t(0.0, 0.0, -1.0);
	}

	inline static vector_t Back() {
		return vector_t(0.0, 0.0, 1.0);
	}

	inline vector_t Right() {
		return vector_t(1.0, 0.0, 0.0);
	}

	inline vector_t Left() {
		return vector_t(-1.0, 0.0, 0.0);
	}

	//�o�͗p
	inline friend std::ostream& operator << (std::ostream& _os, const vector_t& _v) {
		_os << "(" << _v.x << ", " << _v.y << ", " << _v.z << ")";
		return _os;
	}

	
};

//���K�������x�N�g����V���ɐ���
vector_t VectorNormalized(const vector_t& _v);

//��_�Ԃ̋���
float VectorDistance(const vector_t& _v, const vector_t& _w);

//�x�N�g���̂��ꂼ��̗v�f���������x�N�g�����쐬
vector_t VectorScale(const vector_t& _v, const vector_t& _w);

//�O��
vector_t VectorCross(const vector_t& _v, const vector_t& _w);

//����
float VectorDot(const vector_t& _v, const vector_t& _w);
//�傫��
float VectorMagnitude(const vector_t& _v);
//�傫���̓��
float VectorSqrMagnitude(const vector_t& _v);