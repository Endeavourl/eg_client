
class __declspec(dllimport) INI_Reader
{
public:
	INI_Reader(class INI_Reader const &);
	INI_Reader(void);
	~INI_Reader(void);
	class INI_Reader & operator=(class INI_Reader const &);
	void close(void);
	bool find_header(char const *);
	bool get_bool(unsigned int);
	char const * get_file_name(void)const;
	char const * get_header_ptr(void);
	char const * get_indexed_value(unsigned int);
	int get_line_num(void)const;
	char const * get_line_ptr(void);
	char const * get_name(void)const;
	char const * get_name_ptr(void);
	unsigned int get_num_parameters(void)const;
	void get_state(struct State &)const;
	bool get_value_bool(unsigned int);
	float get_value_float(unsigned int);
	int get_value_int(unsigned int);
	char const * get_value_ptr(void);
	char const * get_value_string(unsigned int);
	char const * get_value_string(void);
	unsigned short const * get_value_wstring(void);
	class Vector  get_vector(void);
	bool is_end(void)const;
	bool is_header(char const *);
	bool is_number(char const *)const;
	bool is_value(char const *);
	bool is_value_empty(unsigned int);
	void log_link(char const *)const;
	bool open(char const *,bool);
	bool open_memory(char const *,unsigned int);
	bool read_header(void);
	bool read_value(void);
	void reset(void);
	void seek(unsigned int);
	void set_state(struct State const &);
	unsigned int tell(void)const;
	double value_num(unsigned int);

public:
	unsigned char data[5480];
};

////////////////////////////////////////////////////////////////////////////////////////

class __declspec(dllimport) RenderDisplayList
{
public:
	RenderDisplayList(class RenderDisplayList const &);
	RenderDisplayList(void);
	~RenderDisplayList(void);
	class RenderDisplayList & operator=(class RenderDisplayList const &);
	void execute(class TextRenderContext &,bool);
	void get_dimensions(class TextRenderContext &,float &,float &,float &);
	int get_element_count(void)const ;
	bool get_element_pos(class TextRenderContext &,int,float &,float &,float &);
	void optimize(void);
	void update(float);

public:
	unsigned char data[2048];
};

////////////////////////////////////////////////////////////////////////////////////////

class __declspec(dllimport) BinaryRDLReader
{
public:
	BinaryRDLReader(class BinaryRDLReader const &);
	BinaryRDLReader(void);
	class BinaryRDLReader & operator=(class BinaryRDLReader const &);
	virtual bool extract_text_from_buffer(unsigned short *,unsigned int,unsigned int &,char const *,unsigned int);
	virtual bool read_buffer(class RenderDisplayList &,char const *,unsigned int);
	virtual bool read_file(class RenderDisplayList &,char const *);
	
public:
	unsigned char data[2048];
};

////////////////////////////////////////////////////////////////////////////////////////

class __declspec(dllimport) BinaryRDLWriter
{
public:
	BinaryRDLWriter(class BinaryRDLWriter const &);
	BinaryRDLWriter(void);
	class BinaryRDLWriter & operator=(class BinaryRDLWriter const &);
	virtual bool write_buffer(class RenderDisplayList const &,char *,unsigned int,unsigned int &);
	virtual bool write_file(class RenderDisplayList const &,char const *);
	
public:
	unsigned char data[2048];
};

////////////////////////////////////////////////////////////////////////////////////////

class __declspec(dllimport) XMLReader
{
public:
	XMLReader(class XMLReader const &);
	XMLReader(void);
	class XMLReader & operator=(class XMLReader const &);
	virtual bool extract_text_from_buffer(unsigned short *,unsigned int,unsigned int &,char const *,unsigned int);
	virtual bool read_buffer(class RenderDisplayList &,char const *,unsigned int);
	virtual bool read_file(class RenderDisplayList &,char const *);
	
public:
	unsigned char data[2048];
};

////////////////////////////////////////////////////////////////////////////////////////

class __declspec(dllimport) XMLWriter
{
public:
	XMLWriter(class XMLWriter const &);
	XMLWriter(void);
	class XMLWriter & operator=(class XMLWriter const &);
	virtual bool write_buffer(class RenderDisplayList const &,char *,unsigned int,unsigned int &);
	virtual bool write_file(class RenderDisplayList const &,char const *);
	
public:
	unsigned char data[2048];
};

////////////////////////////////////////////////////////////////////////////////////////

bool __declspec(dllimport) SinglePlayer(void);

///
////////////////////////////////////////////////////////////////////////////////////////
///
