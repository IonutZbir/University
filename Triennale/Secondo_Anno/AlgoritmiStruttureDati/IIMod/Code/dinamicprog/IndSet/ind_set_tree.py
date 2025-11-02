class Opt:
    def __init__(self) -> None:
        self.cv = 0
        self.sv = 0
        self.opt = 0
    
    def to_string(self):
        return f"OPT: {self.opt}, OPTCV: {self.cv}, OPTSV: {self.sv}"

class TreeNode:
    def __init__(self, val = 0, attr = None):
        self.val = val
        self.children = []
        self.attr = attr

class Tree:
    def __init__(self):
        self.root = None

    def print_tree(self, node, depth=0):
        if node is None:
            return
        print("  " * depth + "[" + str(node.val) + "]" + " " + str(node.attr.to_string()))
        for child in node.children:
            self.print_tree(child, depth + 1)
    
def compute_solution(tree: Tree, root: TreeNode, parent: TreeNode = None, visited = None):
    
    if visited is None:
        visited = set()
    
    visited.add(root)
    
    root.attr.sv = 0
    root.attr.cv = root.val
    root.attr.opt = max(root.attr.sv, root.attr.cv)
    
    for nd in root.children:
        if nd != parent and nd not in visited:
            compute_solution(tree, nd, root, visited)
            root.attr.sv += nd.attr.opt
            root.attr.cv += nd.attr.sv
        
    root.attr.opt = max(root.attr.sv, root.attr.cv)

    return

t = Tree()
t.root = TreeNode(2, Opt())
sx = TreeNode(7, Opt())
sx.children = [TreeNode(3, Opt()), TreeNode(1, Opt())]
dx = TreeNode(6, Opt())
dx.children = [TreeNode(2, Opt()), TreeNode(3, Opt()), TreeNode(3, Opt())]

t.root.children = [sx, dx]

compute_solution(t, t.root)
t.print_tree(t.root)
