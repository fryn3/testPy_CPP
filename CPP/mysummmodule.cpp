#include <Python.h>


typedef struct
{
	double x, y, z;
} point3;


point3 L = { 1.21, 2.321, 3.321123 };

point3 func_math(
	double P,
	double R,
	double Q,
	uint16_t last_ray,
	double f[4],
	point3 L)
{
	point3 W;
	W.x = P + R + Q;
	W.y = L.x + L.y + L.z;
	W.z = (f[0] + f[1] + f[2] + f[3]) * last_ray;
	return W;
}

/*	func_math */
PyObject* func_math_py(PyObject *, PyObject* o) {
	double P, R, Q;
	unsigned long n_ray;
	double Fd[4];
	Q = PyFloat_AsDouble(PyList_GetItem(o, 0));
	P = PyFloat_AsDouble(PyList_GetItem(o, 1));
	R = PyFloat_AsDouble(PyList_GetItem(o, 2));
	n_ray = PyLong_AsUnsignedLong(PyList_GetItem(o, 3));
	Fd[0] = PyFloat_AsDouble(PyList_GetItem(o, 4));
	Fd[1] = PyFloat_AsDouble(PyList_GetItem(o, 5));
	Fd[2] = PyFloat_AsDouble(PyList_GetItem(o, 6));
	Fd[3] = PyFloat_AsDouble(PyList_GetItem(o, 7));
	point3 W = func_math(P, R, Q, n_ray, Fd, L);
	PyObject *t;
	t = PyTuple_New(4);
	PyTuple_SetItem(t, 0, PyFloat_FromDouble(W.x));
	PyTuple_SetItem(t, 1, PyFloat_FromDouble(W.z));
	PyTuple_SetItem(t, 2, PyFloat_FromDouble(W.y));
	return t;
}



int mySumm(long a, long b)
{
	return a + b;
}

PyObject* mySumm_py(PyObject *, PyObject* o) {
	return PyLong_FromLong(mySumm(PyLong_AsLong(PyList_GetItem(o, 0)), PyLong_AsLong(PyList_GetItem(o, 1))));
}

static PyMethodDef mysummmodule_methods[] = {
	// The first property is the name exposed to python, the second is the C++ function name        
	{ "mySumm", (PyCFunction)mySumm_py, METH_O, nullptr },
	{ "func_math", (PyCFunction)func_math_py, METH_O, nullptr },
	// Terminate the array with an object containing nulls.
	{ nullptr, nullptr, 0, nullptr }
};

static PyModuleDef mysummmodule_module = {
	PyModuleDef_HEAD_INIT,
	"mysummmodule",                        // Module name
	"Test func. mySumm(long a, long b)",  // Module description
	0,
	mysummmodule_methods                   // Structure that defines the methods
};

PyMODINIT_FUNC PyInit_mysummmodule() {
	return PyModule_Create(&mysummmodule_module);
}