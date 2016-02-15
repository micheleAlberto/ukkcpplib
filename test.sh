echo "test python module"
export PYTHONPATH=${PYTHONPATH}:bin/
python test/import_test.py
python test/tree_test.py
python test/query_test.py
