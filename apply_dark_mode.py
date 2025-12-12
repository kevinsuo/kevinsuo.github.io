import os
import sys

def apply_dark_mode(file_path):
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            content = f.read()
    except FileNotFoundError:
        print(f"Error: File not found at {file_path}")
        return

    # Add CSS links to head
    if '</head>' in content:
        head_end_index = content.find('</head>')
        if 'toggle.css' not in content:
            content = content[:head_end_index] + '  <link rel="stylesheet" href="../../../toggle.css">\n' + content[head_end_index:]
        if 'dark-mode.css' not in content:
            head_end_index = content.find('</head>')
            content = content[:head_end_index] + '  <link rel="stylesheet" href="../../../dark-mode.css">\n' + content[head_end_index:]

    # Modify body tag
    if '<body' in content:
        body_tag_start = content.find('<body')
        body_tag_end = content.find('>', body_tag_start)
        if body_tag_end != -1:
            body_tag = content[body_tag_start:body_tag_end+1]
            
            new_body_tag = body_tag.replace('style="background-color:#ffffff;"', '')
            new_body_tag = new_body_tag.replace('bgcolor=white', '')

            if 'class=' not in new_body_tag:
                new_body_tag = new_body_tag.replace('<body', '<body class=""')
            
            content = content.replace(body_tag, new_body_tag)

    # Add toggle switch
    if '<body' in content:
        body_start_index = content.find('<body')
        body_end_index = content.find('>', body_start_index)
        if body_end_index != -1:
            toggle_html = '''
  <div class="toggle-container">
      <label class="toggle-switch">
          <input type="checkbox" id="darkModeToggle">
          <span class="slider"></span>
      </label>
  </div>
'''
            if 'id="darkModeToggle"' not in content:
                content = content[:body_end_index+1] + toggle_html + content[body_end_index+1:]

    # Add javascript
    if '</body>' in content and 'id="darkModeToggle"' in content:
        body_end_index = content.find('</body>')
        script_html = '''
<script>
    const darkModeToggle = document.getElementById('darkModeToggle');
    const body = document.body;
    const prefersDarkScheme = window.matchMedia('(prefers-color-scheme: dark)');

    function setTheme(theme) {
        if (theme === 'dark') {
            body.classList.add('dark-mode');
        } else {
            body.classList.remove('dark-mode');
        }
        darkModeToggle.checked = theme === 'dark';
        try {
            localStorage.setItem('darkMode', theme);
        } catch (e) {
            console.error('Failed to set dark mode in localStorage', e);
        }
    }

    let savedTheme = null;
    try {
        savedTheme = localStorage.getItem('darkMode');
    } catch (e) {
        console.error('Failed to get dark mode from localStorage', e);
    }

    if (savedTheme) {
        setTheme(savedTheme);
    } else if (prefersDarkScheme.matches) {
        setTheme('dark');
    } else {
        setTheme('light');
    }

    darkModeToggle.addEventListener('change', () => {
        const theme = darkModeToggle.checked ? 'dark' : 'light';
        setTheme(theme);
    });

    prefersDarkScheme.addEventListener('change', (e) => {
        const theme = e.matches ? 'dark' : 'light';
        let storedTheme = null;
        try {
            storedTheme = localStorage.getItem('darkMode');
        } catch (e) {
            console.error('Failed to get dark mode from localStorage', e);
        }
        if (!storedTheme) {
            setTheme(theme);
        }
    });
</script>
'''
        if "const darkModeToggle" not in content:
             content = content[:body_end_index] + script_html + content[body_end_index:]

    try:
        with open(file_path, 'w', encoding='utf-8') as f:
            f.write(content)
    except Exception as e:
        print(f"Error writing to file {file_path}: {e}")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python apply_dark_mode.py <file1> <file2> ...")
        sys.exit(1)
        
    for file_path in sys.argv[1:]:
        apply_dark_mode(file_path)
