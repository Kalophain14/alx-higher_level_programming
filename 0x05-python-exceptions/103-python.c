#include <Python.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

/**
 * print_python_list - Prints basic info about Python lists.
 * @p: A PyObject list object.
 */
void print_python_list(PyObject *p)
{
	Py_ssize_t list_size, list_alloc, index;
	const char *item_type;
	PyListObject *list_obj = (PyListObject *)p;
	PyVarObject *var_obj = (PyVarObject *)p;

	list_size = var_obj->ob_size;
	list_alloc = list_obj->allocated;

	fflush(stdout);

	printf("[*] Python list info\n");
	if (strcmp(p->ob_type->tp_name, "list") != 0)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}

	printf("[*] Size of the Python List = %ld\n", list_size);
	printf("[*] Allocated = %ld\n", list_alloc);

	for (index = 0; index < list_size; index++)
	{
		item_type = list_obj->ob_item[index]->ob_type->tp_name;
		printf("Element %ld: %s\n", index, item_type);
		if (strcmp(item_type, "bytes") == 0)
			print_python_bytes(list_obj->ob_item[index]);
		else if (strcmp(item_type, "float") == 0)
			print_python_float(list_obj->ob_item[index]);
	}
}

/**
 * print_python_bytes - Prints basic info about Python byte objects.
 * @p: A PyObject byte object.
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t byte_size, byte_index;
	PyBytesObject *byte_obj = (PyBytesObject *)p;

	fflush(stdout);

	printf("[.] bytes object info\n");
	if (strcmp(p->ob_type->tp_name, "bytes") != 0)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	printf("  size: %ld\n", ((PyVarObject *)p)->ob_size);
	printf("  trying string: %s\n", byte_obj->ob_sval);

	if (((PyVarObject *)p)->ob_size >= 10)
		byte_size = 10;
	else
		byte_size = ((PyVarObject *)p)->ob_size + 1;

	printf("  first %ld bytes: ", byte_size);
	for (byte_index = 0; byte_index < byte_size; byte_index++)
	{
		printf("%02hhx", byte_obj->ob_sval[byte_index]);
		if (byte_index == (byte_size - 1))
			printf("\n");
		else
			printf(" ");
	}
}

/**
 * print_python_float - Prints basic info about Python float objects.
 * @p: A PyObject float object.
 */
void print_python_float(PyObject *p)
{
	char *float_str = NULL;

	PyFloatObject *float_obj = (PyFloatObject *)p;

	fflush(stdout);

	printf("[.] float object info\n");
	if (strcmp(p->ob_type->tp_name, "float") != 0)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}

	float_str = PyOS_double_to_string(float_obj->ob_fval, 'r', 0,
			Py_DTSF_ADD_DOT_0, NULL);
	printf("  value: %s\n", float_str);
	PyMem_Free(float_str);
}
