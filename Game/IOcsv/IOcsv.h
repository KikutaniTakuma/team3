#pragma once

#include <vector>
#include <string>

class IOcsv {
private:
	inline IOcsv(){}
	inline ~IOcsv(){}

public:
	/*
	csv�t�@�C�����J�������ɐ����ƕ�������ʂ��đ������

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(int �^)
	��R�����F�ϒ��z��(string �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, std::vector<int>& data, std::vector<std::string>& coment);

	/*
	csv�t�@�C�����J�������ɐ����ƕ�������ʂ��đ������
	 
	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(float �^)
	��R�����F�ϒ��z��(string �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, std::vector<float>& data, std::vector<std::string>& coment);

	/*
	csv�t�@�C�����J�������ɐ�����������

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(int �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, std::vector<int>& data);

	/*
	csv�t�@�C�����J�������ɐ�����������

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(float �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, std::vector<float>& data);

	/*
	csv�t�@�C�����J�������ɕ������������

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(string �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, std::vector<std::string>& coment);

	/*
	csv�t�@�C�����J���z��ɑ��

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(int �^)
	��R�����F�v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, int* data, const int& index);

	/*
	csv�t�@�C�����J���z��ɑ��

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(float �^)
	��R�����F�v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, float* data, const int& index);

	/*
	��������g���̂͂����߂��Ȃ�(�f�[�^�̃o�b�t�@�[��p�ӂ���̂��ʓ|�Ȃ̂ł��ƂȂ���string�^��vector�g���Ă�������)��
	�o�b�t�@�[�̗p�ӗ�
	char hoge[4][10] = {NULL};
	char* p[] = {hoge[0],hoge[1],hoge[2],hoge[3]};
	���߂�ǂ��ˁH����Ƃ��̃o�b�t�@�[�̓���邱�Ƃ̂ł��镶����̍ő��10�����ł���𒴂�����̂̓o�O��

	csv�t�@�C�����J���z��ɑ��

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(char* �^)
	��R�����F�v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Input(const char* fileName, char** data, const int& index);


	//==================================================================================================================================

	/*
	csv�t�@�C���ɕ����Ɛ������P�Â��ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(int �^)
	��R�����F�ϒ��z��(string �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, const std::vector<int>& data, const std::vector<std::string>& coment);

	/*
	csv�t�@�C���ɕ����Ɛ������P�Â��ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(float �^)
	��R�����F�ϒ��z��(string �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, const std::vector<float> &data, const std::vector<std::string> &coment);

	/*
	csv�t�@�C���ɐ������P���ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(int �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, const std::vector<int>& data);

	/*
	csv�t�@�C���ɐ������P���ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(float �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, const std::vector<float>& data);

	/*
	csv�t�@�C���ɕ�������P���ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�ϒ��z��(string �^)

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, const std::vector<std::string>& coment);

	/*
	csv�t�@�C���ɕ����Ɛ������P�Â��ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(int �^)
	��R�����F���l�z��̗v�f��
	��S�����F�z��̃|�C���^(const char* �^)
	��T�����F������z��̗v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, int* data, const int& dataIndex, const char** coment, const int& comeIndex);

	/*
	csv�t�@�C���ɕ����Ɛ������P�Â��ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(float �^)
	��R�����F���l�z��̗v�f��
	��S�����F�z��̃|�C���^(const char* �^)
	��T�����F������z��̗v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, float* data, const int& dataIndex, const char** coment, const int& comeIndex);

	/*
	csv�t�@�C���ɐ������P���ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(int �^)
	��R�����F�v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, int* data, const int& index);

	/*
	csv�t�@�C���ɐ������P���ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(float �^)
	��R�����F�v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, float* data, const int& index);

	/*
	csv�t�@�C���ɕ������P���ꂽ����s���J��Ԃ��ĕۑ�(�t�@�C�����Ȃ������ꍇ��������)

	��P�����F�t�@�C���̖��O
	��Q�����F�z��̃|�C���^(const char* �^)
	��R�����F�v�f��

	�߂�l
	0�F����
	1�F���s
	*/
	static int Output(const char* fileName, const char** data, const int& index);
};