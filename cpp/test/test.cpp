#include <jsonwc.h>
#include <stdio.h>
#include <stdexcept>

namespace
{
	class FileInputStream : public jsonwc::IInputStream
	{
		FILE *_f;

	public:
		FileInputStream(const std::string &name): _f(fopen(name.c_str(), "rt")) {
			if (!_f)
				throw std::runtime_error("could not open " + name);
		}
		~FileInputStream() { fclose(_f); }

		FileInputStream(const FileInputStream &) = delete;
		FileInputStream& operator= (const FileInputStream &) = delete;

		int Read(void *data, int size) override
		{
			printf("read %p %d\n", data, size);
			return fread(data, 1, size, _f);
		}
	};

	struct Receiver :
		public virtual jsonwc::IJsonArrayReceiver,
		public virtual jsonwc::IJsonObjectReceiver,
		public virtual jsonwc::IJsonValueReceiver,
		public virtual jsonwc::IObjectReceiver,
		public virtual jsonwc::IValueReceiver
	{
		jsonwc::IReceiver * Finish() override
		{ printf("finish\n"); return this; }

		void OnNull() override
		{ printf("null\n"); }
		void OnBool(bool value)
		{ printf("bool %s\n", value? "true": "false"); }
		void OnInteger(jsonwc::IntegerType value) override
		{ printf("integer %ld\n", (long)value); }
		void OnNumber(jsonwc::NumberType value) override
		{ printf("number %lg\n", value); }
		void OnString(std::string && value) override
		{ printf("string %s\n", value.c_str()); }
		IJsonArrayReceiver * OnJsonArray() override
		{ printf("json-array\n"); return this; }
		IJsonObjectReceiver * OnJsonObject() override
		{ printf("json-object\n"); return this; }
		IObjectReceiver * OnObject(std::string && type) override
		{ printf("object %s\n", type.c_str()); return this; }
		IValueReceiver * OnObjectProperty(std::string && name) override
		{ printf("property %s\n", name.c_str()); return this; }
		IJsonValueReceiver * OnArrayValue() override
		{ printf("array-value\n"); return this; }
	};

}

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "usage: <jsonwc file>\n");
		return 1;
	}
	FileInputStream fis(argv[1]);

	Receiver recv;
	jsonwc::Parser parser(&recv);
	parser.Parse(fis);

	return 0;
}