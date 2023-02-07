#include "IOcsv.h"

#include <fstream>
#include <sstream>
#include <algorithm>

int IOcsv::Input(const char* fileName, std::vector<int>& data, std::vector<std::string>& coment)
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@�[
		std::string lineBuff;
		std::string buff;

		// �C�e���[�^
		auto id = data.begin();
		auto ic = coment.begin();

		// �����̗v�f���o�b�t�@�[
		auto dataSize = data.size();
		auto dataNum = 0;
		auto comeSize = coment.size();
		auto comeNum = 0;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// buff�Ɋi�[����Ă��镶�������ׂĐ����Ȃ琔�l(int�^)�ɕς��đ��
				if (std::all_of(buff.cbegin(), buff.cend(), isdigit))
				{
					if (dataNum >= dataSize) {
						data.push_back(stoi(buff));
					}
					else {
						*id = stoi(buff);// string��int�֕ϊ����ۑ�
						id++;
						dataNum++;
					}
				}
				// buff�Ɋi�[����Ă��镶���Ɉ�ł������ȊO�������Ă�����buff�����̂܂ܑ��
				else if (std::any_of(buff.cbegin(), buff.cend(), isalpha))
				{
					if (comeNum >= comeSize) {
						coment.push_back(buff);
					}
					else {
						*ic = buff;
						ic++;
						comeNum++;
					}
				}
			}
		}

		return 0;
	}
}

int IOcsv::Input(const char* fileName, std::vector<float>& data, std::vector<std::string>& coment) 
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@
		std::string lineBuff;
		std::string buff;

		// �C�e���[�^
		auto id = data.begin();
		auto ic = coment.begin();

		// �����̗v�f���o�b�t�@�[
		auto dataSize = data.size();
		auto dataNum = 0;
		auto comeSize = coment.size();
		auto comeNum = 0;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// buff�Ɋi�[����Ă��镶���ɐ������ꕶ���ł��܂܂�Ă����琔�l(float�^)�ɕς��đ��
				if (std::any_of(buff.cbegin(), buff.cend(), isdigit))
				{
					if (dataNum >= dataSize) {
						data.push_back(stof(buff));
					}
					else {
						*id = stof(buff);// string��float�֕ϊ����ۑ�
						id++;
						dataNum++;
					}
				}
				// buff�Ɋi�[����Ă��镶�������ׂĕ�����������buff�����̂܂ܑ��
				else if (std::all_of(buff.cbegin(), buff.cend(), isalpha))
				{
					if (comeNum >= comeSize) {
						coment.push_back(buff);
					}
					else {
						*ic = buff;
						ic++;
						comeNum++;
					}
				}
			}
		}

		return 0;
	}
}

int IOcsv::Input(const char* fileName, std::vector<int>& data)
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@
		std::string lineBuff;
		std::string buff;

		// �C�e���[�^
		auto id = data.begin();

		// �����̗v�f���o�b�t�@�[
		auto size = data.size();
		auto num = 0;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// buff�Ɋi�[����Ă��镶�������ׂĐ����Ȃ琔�l(int�^)�ɕς��đ��
				if (std::all_of(buff.cbegin(), buff.cend(), isdigit))
				{
					if (num >= size) {
						data.push_back(stoi(buff));
					}
					else {
						*id = stoi(buff);// string��int�֕ϊ����ۑ�
						id++;
						num++;
					}
				}
			}
		}

		return 0;
	}
}

int IOcsv::Input(const char* fileName, std::vector<float>& data) 
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@
		std::string lineBuff;
		std::string buff;

		// �C�e���[�^
		auto id = data.begin();

		// �����̗v�f���o�b�t�@�[
		auto size = data.size();
		auto num = 0;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// buff�Ɋi�[����Ă��镶�������ׂĐ����Ȃ琔�l(float�^)�ɕς��đ��
				if (std::any_of(buff.cbegin(), buff.cend(), isdigit))
				{
					if (num >= size) {
						data.push_back(stof(buff));
					}
					else {
						*id = stof(buff);// string��float�֕ϊ����ۑ�
						id++;
						num++;
					}
				}
			}
		}

		return 0;
	}
}

int IOcsv::Input(const char* fileName, std::vector<std::string>& coment) 
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@
		std::string lineBuff;
		std::string buff;

		// �C�e���[�^
		auto ic = coment.begin();

		// �����̗v�f���o�b�t�@�[
		auto size = coment.size();
		auto num = 0;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// buff�Ɋi�[����Ă��镶�������ׂĕ����Ȃ���
				if (std::all_of(buff.cbegin(), buff.cend(), isalnum))
				{
					if (num >= size) {
						coment.push_back(buff);
					}
					else {
						*ic = buff;
						ic++;
						num++;
					}
				}
			}
		}

		return 0;
	}
}

int IOcsv::Input(const char* fileName, int* data, const int& index) 
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �v�f���o�b�t�@�[
	int num = 0;

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@
		std::string lineBuff;
		std::string buff;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// buff�Ɋi�[����Ă��镶�������ׂĐ����Ȃ琔�l(int�^)�ɕς��đ��
				if (std::all_of(buff.cbegin(), buff.cend(), isdigit))
				{
					// �f�[�^�o�b�t�@�[���v�f���𒴂��Ă�����I��
					if (num >= index) {
						return 0;
					}

					data[num] = stoi(buff);// string��int�֕ϊ����ۑ�
					num++;
				}
			}
		}

		return 0;
	}
}

int IOcsv::Input(const char* fileName, float* data, const int& index) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �v�f���o�b�t�@�[
	int num = 0;

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@
		std::string lineBuff;
		std::string buff;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// buff�Ɋi�[����Ă��镶�������ׂĐ����Ȃ琔�l(float�^)�ɕς��đ��
				if (std::any_of(buff.cbegin(), buff.cend(), isdigit))
				{
					// �f�[�^�o�b�t�@�[���v�f���𒴂��Ă�����I��
					if (num >= index) {
						return 0;
					}

					data[num] = stof(buff);// string��float�֕ϊ����ۑ�
					num++;
				}
			}
		}

		return 0;
	}
}

int IOcsv::Input(const char* fileName, char** data, const int& index) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ifstream fileBuff(fileName);

	// �v�f���o�b�t�@�[
	int num = 0;

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// �o�b�t�@
		std::string lineBuff;
		std::string buff;

		// ��s�擾
		while (getline(fileBuff, lineBuff))
		{
			// �ϊ�
			std::istringstream line(lineBuff);

			// ��؂蕶���ȑO��string���擾
			while (getline(line, buff, ','))
			{
				// �f�[�^�o�b�t�@�[���v�f���𒴂��Ă�����I��
				if (num >= index) {
					return 0;
				}

				int index = 0;
				for (char& i : buff) {
					data[num][index] = i; // �ꕶ���Â��
					index++;
				}
				num++;
			}
		}

		return 0;
	}
}

///====================================================================================================================================
///====================================================================================================================================
///====================================================================================================================================

int IOcsv::Output(const char* fileName, const std::vector<int>& data, const std::vector<std::string>& coment)
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	// ���͏���
	else
	{
		// for���̃o�b�t�@�[
		int num = 0;
		if (data.size() > coment.size()) { num = static_cast<int>(data.size()); }
		else if (data.size() <= coment.size()) { num = static_cast<int>(coment.size()); }

		auto id = data.begin();
		auto ic = coment.begin();
		for (int i = 0; i < num; i++)
		{
			if (i >= static_cast<int>(data.size())) {
				fileBuff << *ic << "," << std::endl;
			}
			else if (i >= static_cast<int>(coment.size())) {
				fileBuff << *id << "," << std::endl;
			}
			else {
				fileBuff << *ic << "," << *id << "," << std::endl;
			}

			if (id != data.end()) { ++id; }
			if (ic != coment.end()) { ++ic; }
		}
		return 0;
	}
}

int IOcsv::Output(const char* fileName, const std::vector<float>& data, const std::vector<std::string>& coment) 
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	// ���͏���
	else 
	{
		// for���̃o�b�t�@�[
		int num = 0;
		if (data.size() > coment.size()) { num = static_cast<int>(data.size()); }
		else if(data.size() <= coment.size()) { num = static_cast<int>(coment.size()); }

		auto id = data.begin();
		auto ic = coment.begin();
		for (int i = 0; i < num; i++)
		{
			if (i >= static_cast<int>(data.size())) {
				fileBuff << *ic << "," << std::endl; 
			}
			else if (i >= static_cast<int>(coment.size())) {
				fileBuff << *id << "," << std::endl; 
			}
			else { 
				fileBuff << *ic << "," << *id << "," << std::endl; 
			}

			if (id != data.end()) { ++id; }
			if (ic != coment.end()) { ++ic; }
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, const std::vector<int>& data)
{
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// ���͏���
		for (auto& id : data)
		{
			fileBuff << id << "," << std::endl;
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, const std::vector<float>& data) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	// ���͏���
	else 
	{
		for (auto& id : data) 
		{
			fileBuff << id << "," << std::endl;
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, const std::vector<std::string>& coment) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	// ���͏���
	else 
	{
		for (auto& ic : coment) 
		{
			fileBuff << ic << "," << std::endl;
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, int* data, const int& dataIndex, const char** coment, const int& comeIndex) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	// ���͏���
	else
	{
		// for���̃o�b�t�@�[
		int num = 0;
		if (dataIndex > comeIndex) { num = dataIndex; }
		else if (dataIndex <= comeIndex) { num = comeIndex; }

		for (int i = 0; i < num; i++)
		{
			if (i >= dataIndex && i < comeIndex) {
				fileBuff << coment[i] << "," << std::endl;
			}
			else if (i < dataIndex && i >= comeIndex) {
				fileBuff << data[i] << "," << std::endl;
			}
			else {
				fileBuff << coment[i] << "," << data[i] << "," << std::endl;
			}
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, float* data, const int& dataIndex, const char** coment, const int& comeIndex) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	// ���͏���
	else
	{
		// for���̃o�b�t�@�[
		int num = 0;
		if (dataIndex > comeIndex) { num = dataIndex; }
		else if (dataIndex <= comeIndex) { num = comeIndex; }

		for (int i = 0; i < num; i++)
		{
			if (i >= dataIndex && i < comeIndex) {
				fileBuff << coment[i] << "," << std::endl;
			}
			else if (i < dataIndex && i >= comeIndex) {
				fileBuff << data[i] << "," << std::endl;
			}
			else {
				fileBuff << coment[i] << "," << data[i] << "," << std::endl;
			}
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, int* data, const int& index) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// ���͏���
		for (int i=0;i<index;i++)
		{
			fileBuff << data[i] << "," << std::endl;
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, float* data, const int& index) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// ���͏���
		for (int i = 0; i < index; i++)
		{
			fileBuff << data[i] << "," << std::endl;
		}

		return 0;
	}
}

int IOcsv::Output(const char* fileName, const char** data, const int& index) {
	// �t�@�C���o�b�t�@�[(�R���X�g���N�^�ŊJ��)
	std::ofstream fileBuff(fileName);

	// �����t�@�C�����J���Ȃ�������A�Ȃ�������1��Ԃ�
	if (!fileBuff) { return 1; }

	else
	{
		// ���͏���
		for (int i = 0; i < index; i++)
		{
			fileBuff << data[i] << "," << std::endl;
		}

		return 0;
	}
}

