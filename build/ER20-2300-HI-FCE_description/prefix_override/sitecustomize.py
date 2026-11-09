import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/mario/master_ws/install/ER20-2300-HI-FCE_description'
