#pragma once

#include <string>
#include <vector>

// Utilities for escaping/unescaping fields and splitting lines while preserving escapes.
static std::string escapeField(const std::string &s) {
    std::string out;
    out.reserve(s.size());
    for (char c : s) {
        if (c == '\\') { out += "\\\\"; }
        else if (c == '|') { out += "\\|"; }
        else if (c == '\n') { out += "\\n"; }
        else if (c == ';') { out += "\\;"; }
        else if (c == '~') { out += "\\~"; }
        else out += c;
    }
    return out;
}

static std::string unescapeField(const std::string &s) {
    std::string out;
    out.reserve(s.size());
    for (size_t i = 0; i < s.size(); ++i) {
        if (s[i] == '\\' && i + 1 < s.size()) {
            char next = s[i+1];
            if (next == '\\') { out += '\\'; i++; }
            else if (next == '|') { out += '|'; i++; }
            else if (next == 'n') { out += '\n'; i++; }
            else if (next == ';') { out += ';'; i++; }
            else if (next == '~') { out += '~'; i++; }
            else { out += next; i++; }
        } else out += s[i];
    }
    return out;
}

static std::vector<std::string> splitEscaped(const std::string &line, char sep='|') {
    std::vector<std::string> parts;
    std::string cur;
    bool esc = false;
    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];
        if (!esc) {
            if (c == '\\') { esc = true; continue; }
            if (c == sep) { parts.push_back(cur); cur.clear(); continue; }
            cur.push_back(c);
        } else {
            // keep escape sequences so unescapeField can process them
            cur.push_back('\\');
            cur.push_back(c);
            esc = false;
        }
    }
    parts.push_back(cur);
    return parts;
}
