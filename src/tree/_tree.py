# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.11
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('__tree', [dirname(__file__)])
        except ImportError:
            import __tree
            return __tree
        if fp is not None:
            try:
                _mod = imp.load_module('__tree', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    __tree = swig_import_helper()
    del swig_import_helper
else:
    import __tree
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0


class UkkTree(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, UkkTree, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, UkkTree, name)
    __repr__ = _swig_repr
    __swig_setmethods__["opt"] = __tree.UkkTree_opt_set
    __swig_getmethods__["opt"] = __tree.UkkTree_opt_get
    if _newclass:opt = _swig_property(__tree.UkkTree_opt_get, __tree.UkkTree_opt_set)
    __swig_setmethods__["text"] = __tree.UkkTree_text_set
    __swig_getmethods__["text"] = __tree.UkkTree_text_get
    if _newclass:text = _swig_property(__tree.UkkTree_text_get, __tree.UkkTree_text_set)
    __swig_setmethods__["text_index"] = __tree.UkkTree_text_index_set
    __swig_getmethods__["text_index"] = __tree.UkkTree_text_index_get
    if _newclass:text_index = _swig_property(__tree.UkkTree_text_index_get, __tree.UkkTree_text_index_set)
    __swig_setmethods__["n_leafs"] = __tree.UkkTree_n_leafs_set
    __swig_getmethods__["n_leafs"] = __tree.UkkTree_n_leafs_get
    if _newclass:n_leafs = _swig_property(__tree.UkkTree_n_leafs_get, __tree.UkkTree_n_leafs_set)
    __swig_setmethods__["root"] = __tree.UkkTree_root_set
    __swig_getmethods__["root"] = __tree.UkkTree_root_get
    if _newclass:root = _swig_property(__tree.UkkTree_root_get, __tree.UkkTree_root_set)
    __swig_setmethods__["last_leaf_node"] = __tree.UkkTree_last_leaf_node_set
    __swig_getmethods__["last_leaf_node"] = __tree.UkkTree_last_leaf_node_get
    if _newclass:last_leaf_node = _swig_property(__tree.UkkTree_last_leaf_node_get, __tree.UkkTree_last_leaf_node_set)
    __swig_setmethods__["last_leaf"] = __tree.UkkTree_last_leaf_set
    __swig_getmethods__["last_leaf"] = __tree.UkkTree_last_leaf_get
    if _newclass:last_leaf = _swig_property(__tree.UkkTree_last_leaf_get, __tree.UkkTree_last_leaf_set)
    def __init__(self): 
        this = __tree.new_UkkTree()
        try: self.this.append(this)
        except: self.this = this
    def location_downward(self, *args): return __tree.UkkTree_location_downward(self, *args)
    def edgeLenght(self, *args): return __tree.UkkTree_edgeLenght(self, *args)
    def common_substring_lenght(self, *args): return __tree.UkkTree_common_substring_lenght(self, *args)
    def split_edge(self, *args): return __tree.UkkTree_split_edge(self, *args)
    def add_substring_to_node(self, *args): return __tree.UkkTree_add_substring_to_node(self, *args)
    def add_substring_to_node_iterative(self, *args): return __tree.UkkTree_add_substring_to_node_iterative(self, *args)
    def add_symbol(self, *args): return __tree.UkkTree_add_symbol(self, *args)
    def substring(self, *args): return __tree.UkkTree_substring(self, *args)
    def leafString(self, *args): return __tree.UkkTree_leafString(self, *args)
    def edgeString(self, *args): return __tree.UkkTree_edgeString(self, *args)
    def search(self, *args): return __tree.UkkTree_search(self, *args)
    def count(self, *args): return __tree.UkkTree_count(self, *args)
    __swig_destroy__ = __tree.delete_UkkTree
    __del__ = lambda self : None;
UkkTree_swigregister = __tree.UkkTree_swigregister
UkkTree_swigregister(UkkTree)

# This file is compatible with both classic and new-style classes.


