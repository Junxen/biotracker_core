#pragma once

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <opencv2/opencv.hpp> // cv::Point, cv::Rect
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Python.h>
#include <boost/python.hpp>
#include <iostream>
#include <numpy/ndarrayobject.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wold-style-cast"

static PyObject *opencv_error = 0;

int failmsg(const char *fmt, ...);

class PyAllowThreads;

class PyEnsureGIL;

#define ERRWRAP2(expr) \
try \
{ \
    PyAllowThreads allowThreads; \
    expr; \
} \
catch (const cv::Exception &e) \
{ \
    PyErr_SetString(opencv_error, e.what()); \
    return 0; \
}

PyObject *failmsgp(const char *fmt, ...);

static size_t REFCOUNT_OFFSET = (size_t)&(((PyObject *)0)->ob_refcnt) +
                                (0x12345678 != *(const size_t *)"\x78\x56\x34\x12\0\0\0\0\0")*sizeof(int);

static inline PyObject *pyObjectFromRefcount(const int *refcount) {
    return (PyObject *)((size_t)refcount - REFCOUNT_OFFSET);
}

static inline int *refcountFromPyObject(const PyObject *obj) {
    return (int *)((size_t)obj + REFCOUNT_OFFSET);
}


class NumpyAllocator;

enum { ARG_NONE = 0, ARG_MAT = 1, ARG_SCALAR = 2 };

class NDArrayConverter {
  private:
    void init();
  public:
    NDArrayConverter();
    cv::Mat toMat(const PyObject *o);
    PyObject *toNDArray(const cv::Mat &mat);
};

#pragma GCC diagnostic push

/**
 * Python helper functions
 */
namespace PyHelper {

/**
 * @brief convert
 * @param mat
 * @return
 */
PyObject *convert(const cv::Mat &mat);

/**
 * @brief init
 * Must be called in the main thread and before any other thread is created
 */
void init();

}
