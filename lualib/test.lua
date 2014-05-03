package.path = '/home/lwj/code/lua/luc/chelloworld/lualib/?.lua'
local slt2 = require('slt2')

function escapeHTML(str)
	local tt = {
		['<'] = '&lt;',
		['>'] = '&gt;'
	}
	str = string.gsub(str, '&', '&amp;')
	str = string.gsub(str, '[<>]', tt)
	return str
end

function htmlrender(f,u)
    local tmpl = slt2.loadfile(f)
    return slt2.render(tmpl,{user = u})
end

