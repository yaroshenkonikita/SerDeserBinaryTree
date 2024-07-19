class Codec {
    static constexpr char c_null[] = ",n";

    std::vector<TreeNode*> treeToVector(TreeNode* root) {
        std::vector<TreeNode*> tree{root};
        int current = 0;
        while (current < tree.size()) {
            if (tree[current] == nullptr) {
                ++current;
                continue;
            }
            tree.push_back(tree[current]->left);
            tree.push_back(tree[current++]->right);
        }
        return tree;
    }

    std::string toString(int num) {
        const bool isMinus = num < 0;
        std::string to_string;
        if (isMinus) {
            num *= -1;
        }
        do {
            to_string.push_back(num % 10 + '0');
            num /= 10;
        } while (num > 0);
        if (isMinus) {
            to_string.push_back('-');
        }
        std::reverse(to_string.begin(), to_string.end());
        return to_string;
    }

public:
    std::string serialize(TreeNode* root) {
        if (!root) {
            return "n";
        }
        const std::vector<TreeNode*> tree{treeToVector(root)};
        std::string serialize_line = toString(root->val);
        int nulls = 0;
        for (int i = 1; i < tree.size(); ++i) {
            if (tree[i] == nullptr) {
                ++nulls;
                continue;
            }
            while (nulls) {
                serialize_line.append(c_null);
                --nulls;
            }
            serialize_line.push_back(',');
            serialize_line.append(toString(tree[i]->val));
        }
        return serialize_line;
    }

    TreeNode* deserialize(std::string data) {
        std::stringstream in(data);
        std::string num;
        std::vector<TreeNode*> list;
        while (std::getline(in, num, ',')) {
            if (num[0] == 'n') {
                list.push_back(nullptr);
            } else {
                list.push_back(new TreeNode(std::stoi(num)));
            }
        }
        int current = 0, fast = 1;
        while (fast < list.size()) {
            while (list[current] == nullptr) {
                ++current;
            }
            list[current]->left = list[fast++];
            if (fast == list.size()) {
                break;
            }
            list[current++]->right = list[fast++];
        }
        return list[0];
    }
};
